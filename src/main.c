/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:05 by wchow             #+#    #+#             */
/*   Updated: 2024/09/25 19:38:32 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process(char *input, t_data *data, t_pp *p)
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
	else if (!ft_strncmp(input, "<", 1))
		result = get_infile(data->args, p);
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

void	start(t_data *data, t_pp *p)
{
	while (1)
	{
		data->input = readline("\033[1;33m<<Minishell>>  \033[0m");
		if (data->input && *data->input)
		{
			add_history(data->input); // Add to history if input is not empty
			set_argv(data->input, &(data->args));
			process(data->input, data, p); // Main functions
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
	t_data  *data;
	t_cmd   *cmd;
	t_pp    *pp;

	data = ft_calloc (1, sizeof(t_data));
	cmd = ft_calloc (1, sizeof(t_cmd));
	pp = ft_calloc (1, sizeof(t_pp));

	printf("Type 'help' for available commands\n");

	handle_signals();

	init_struct_ptrs(data, cmd, pp);
	init_data(data, env);
	start(data, pp);
	close_pipes(pp);
	waitpid(-1, NULL, 0);
	free_parent(pp);
	ft_exit(data, true);
	return (0);
}