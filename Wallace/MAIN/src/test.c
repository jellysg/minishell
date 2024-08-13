/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:05 by wchow             #+#    #+#             */
/*   Updated: 2024/08/13 08:13:36 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	sysCall(char *input, t_data *data)
{
	//System Calls

	//Why tf do we have to do this to satisfy Werror my god actually cancer
	char	**argv;
	argv = ft_calloc(2, sizeof(char *));
	argv[0] = ft_strdup(input);
	argv[1] = NULL;
	//i swear this is dumb 

	pid_t	pid;
	int	status;
	if (ft_strchr(input, '/'))
	{
		if (access(input, X_OK) == 0)
		{
			pid = fork();
			if (pid < 0)
				perror("fork failed");
			else if (pid == 0)
				execve(input, argv, data->env);
			else
				waitpid(pid, &status, 0);
		}
		else
			perror("Command not found");
		free(argv[0]);
		free(argv);
		return ;
	}
	
	char	**allPaths = ft_split(data->path, ':'); //An index of all paths, separated by delimiting ':' e.g. /bin:/usr/bin: --> /bin | /usr/bin
	char	*addSlash; //Add a '/' to the back of the individual path
	char	*fullCmd;
	int	i = -1;
	while (allPaths[++i])
	{
		addSlash = ft_strjoin(allPaths[i], "/"); //e.g. /bin -> /bin/
		fullCmd = ft_strjoin(addSlash, input); //Try to plug in input to end of path, see if it's a valid cmd
		free(addSlash);
		if (access(fullCmd, X_OK) == 0) //Means execute suggcess
		{
			pid = fork();
			if (pid < 0)
				perror("fork failed");
			else if (pid == 0)
				execve(fullCmd, argv, data->env);
			else
				waitpid(pid, &status, 0);
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

void	process(char *input, t_data *data)
{
	//Custom Commands
	if (!ft_strncmp(input, "help", 4))
			printf("%s", showCmds);
	else if (!ft_strncmp(input, "echo ", 5))
		ft_printf("%s\n", input + 5);
	else if (!ft_strncmp(input, "env", 3))
		for (int i = 0; data->env[i]; i++)
			printf("%s\n", data->env[i]);
	else if (!ft_strncmp(input, "exit", 4))
	{
		freeData(data);
		exit(0);
	}
	else if (!ft_strncmp(input, "showpath", 8))
		printf("data->path is: %s\n", data->path);
	else
		sysCall(input, data);	
}

void	start(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("<<Nanoshell>>  ");
		if (input && *input)
		{
			add_history(input); // Add to history if input is not empty
			process(input, data); // Main functions
			free(input);
		}
		else if (input == NULL) // Handle Ctrl+D (EOF)
		{
			printf("exit\n");
			break;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data	*data;

	printf("Type 'help' for available commands\n");

	handleSignals();

	data = ft_calloc (1, sizeof(t_data));
	initData(data, env);

	start(data);
	freeData(data);
	return (0);
}