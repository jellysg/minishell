/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:11:22 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 17:11:23 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*For commands that have arguments, this reallocs and resets argv. Triple * cause I need
to use it for process function and pass in the address of argv*/
void	set_argv(char *input, char ***argv, t_data *data)
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
	*argv = ft_split(ft_quote(input, 0, 0, data), ' ');
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
			set_argv(input, &argv, data);
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
			set_argv(input, &argv, data);
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