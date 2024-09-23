/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:05 by wchow             #+#    #+#             */
/*   Updated: 2024/09/23 22:55:17 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*For commands that have arguments, this reallocs and resets argv. Triple * cause I need
to use it for process function and pass in the address of argv*/
void	set_argv(char *input, char ***argv)
{
	int	i;

	if (*argv)
	{
		i = 0;
		while ((*argv)[i])
		{
			free((*argv)[i]);
			i++;
		}
		free(*argv);
	}
	*argv = ft_split(ft_quote(input, 0, 0), ' ');
}

/*Executes program by forking off a child process then main process waits
Uses data for env, input as full command path, argv as the arguments after*/
void	ft_fork_and_exec(t_data *data, char *input, char **argv)
{
	pid_t	pid;
	int	status;

	if (access(input, X_OK) == 0)
	{
		pid = fork();
		if (pid < 0)
			perror("fork failed");
		else if (pid == 0)
		{
			execve(input, argv, data->env);
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
	}
}

/*For system calls from /bin/*/
void	sys_call(char *input, t_data *data)
{
	//System Calls

	//Ok so this is needed for Werror, but turned out useful
	char	**argv;
	argv = ft_calloc(2, sizeof(char *));
	argv[0] = ft_strdup(input);
	argv[1] = NULL;

	/*For direct paths e.g. /bin/pwd*/
	if (ft_strchr(input, '/')) //To check if it's a direct path, then try to execute
	{
		if (access(input, X_OK) == 0)
			ft_fork_and_exec(data, input, argv);
		else if (ft_strchr(input, ' '))
		{
			set_argv(input, &argv);
			ft_fork_and_exec(data, argv[0], argv);
		}
		else
			perror("Command not found");
		free(argv[0]);
		free(argv);
		return ;
	}
	
	/*For non direct calls, AKA macros like "ls" or "pwd" instead of "/bin/ls" or "/bin/pwd"*/
	char	**allPaths = ft_split(data->path, ':'); //An index of all paths, separated by delimiting ':' e.g. /bin:/usr/bin: --> /bin | /usr/bin
	char	*addSlash; //Add a '/' to the back of the individual path
	char	*fullCmd; //Add the command to the back of the path
	int	i = -1;
	while (allPaths[++i]) 
	{
		addSlash = ft_strjoin(allPaths[i], "/"); //e.g. /bin -> /bin/
		//Try to plug in input to end of path, see if it's a valid cmd
		if (ft_strchr(input, ' ')) //If there's argument (ls -a)
		{
			set_argv(input, &argv);
			fullCmd = ft_strjoin(addSlash, argv[0]);
		}
		else  //No argument (ls)
			fullCmd = ft_strjoin(addSlash, input);
		//Try to plug in input to end of path, see if it's a valid cmd
		free(addSlash);
		if (access(fullCmd, X_OK) == 0) //Means execute suggcess
		{
			/* printf("input: %s\n", input);
			for (int i = 0; argv[i]; i++)
				printf("argv[%d] = %s\n", i, argv[i]);
			printf("fullCmd: %s\n", fullCmd); */
			ft_fork_and_exec(data, fullCmd, argv);
			free(fullCmd);
			break ;
		}
		free(fullCmd);
	}
	if (!allPaths[i])
		perror("Command not found");
	i = 0;
	while (allPaths[i])
		free(allPaths[i++]);
	free (allPaths);
	free(argv[0]);
	free(argv);
}

int	process(char *input, t_data *data)
{
	int	result;

	result = 127;
	//Custom Commands
	if (!ft_strncmp(input, "help", 4))
	{
		printf("%s", showCmds);
		result = SUCCESS;
	}
	else if (!ft_strncmp(input, "cd", 2) && (input[2] == ' ' || input[2] == '\0'))
		result = ft_cd(input, data);
	else if (!ft_strncmp(input, "echo ", 5))
		result = ft_echo(input + 5);
	else if (!ft_strncmp(input, "env", 3))
		result = ft_env(data);
	else if (!ft_strncmp(input, "pwd", 3))
		result = ft_pwd(data);
	else if (!ft_strncmp(input, "export", 6))
		result = ft_export(data->args, data);
	else if (!ft_strncmp(input, "unset", 5))
		result = ft_unset(data->args, data);
	else if (!ft_strncmp(input, "exit", 4))
		result = ft_exit(data, false);
	else if (!ft_strncmp(input, "showpath", 8))
	{
		printf("data->path is: %s\n", data->path);
		result = SUCCESS;
	}
	else if (!ft_strncmp(input, "showargs", 8))
  	{
		printf("data->args[0] is: %s\n", data->args[0]);
		result = SUCCESS;
	}
	else if (data->args[0])
	{
		sys_call(input, data);
		result = SUCCESS;
	}
	return (result);
}

void	close_fds(t_cmd *cmd, bool check)
{
	if (cmd->io_fd)
	{
		if (cmd->io_fd->fd_in != -1)
			close(cmd->io_fd->fd_in);
		if (cmd->io_fd->fd_out != -1)
			close(cmd->io_fd->fd_out);
		if (check)
			reinit_io(cmd->io_fd);
	}
	close_pipes(cmd, NULL);
}

int	get_child(t_data *data, t_cmd *cmd)
{
	pid_t	wpid;
	int		temp;
	int		result;

	close_fds(cmd, false);
	temp = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &result, 0);
		if (wpid == data->pid)
			temp = result;
		continue ;
	}
    if (WIFEXITED(temp))
		result = WEXITSTATUS(temp);
	else if (WIFSIGNALED(temp))
		result = 128 + WTERMSIG(temp);
	else
		result = temp;
	return (result);
}

int	init_child(t_data *data, t_cmd *cmd)
{
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (FAILURE);
		else if (data->pid == 0)
			start(data, cmd);
		cmd = cmd->next;
	}
	return (get_child(data, cmd));
}

int	prep_exec(t_data *data, t_cmd *cmd)
{
	if (!data || !cmd)
		return (SUCCESS);
	if (!cmd->command)
	{
		if (cmd->io_fd && !check_io(cmd->io_fd))
			return (FAILURE);
		return (SUCCESS);
	}
	if (!init_pipes(data->cmds, cmd))
		return (FAILURE);
	return (127);
}

int	execute(t_data *data, t_cmd *cmd)
{
	int	result;

	result = prep_exec(data, cmd);
	if (result == 127) // 127 = command not found
		return (result);
	if (!cmd->pipe_out && !cmd->prev && check_io(cmd->io_fd))
	{
		redir_io(cmd->io_fd);
		result = process(data->input, data);
		reinit_io(cmd->io_fd);
		if (result != 127)
			return (result);
	}
	if (result == 127)
		return (init_child(data, cmd));
	return (result);
}

void	start(t_data *data, t_cmd *c)
{
	while (1)
	{
		data->input = readline("\033[1;33m<<Nanoshell>>  \033[0m");
		if (data->input && *data->input)
		{
			add_history(data->input); // Add to history if input is not empty
			set_argv(data->input, &(data->args));
			execute(data, c); // Main functions
			free(data->input);
		}
		else if (data->input == NULL) // Handle Ctrl+D (EOF)
			break;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data	*data;
    t_cmd   *cmd;

	printf("Type 'help' for available commands\n");

	handleSignals();

	data = ft_calloc (1, sizeof(t_data));
	cmd = ft_calloc (1, sizeof(t_cmd));
	initData(data, env);
	start(data, cmd);
	ft_exit(data, true);
	return (0);
}