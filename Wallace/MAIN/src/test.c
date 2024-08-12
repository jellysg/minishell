/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:05 by wchow             #+#    #+#             */
/*   Updated: 2024/08/13 04:52:27 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	process(char *input, t_data *data)
{
	int i = 0;
	if (!ft_strncmp(input, "echo ", 5))
		ft_printf("%s\n", input + 5);
	if (!ft_strncmp(input, "env", 3))
	{
		for (i = 0; data->env[i]; i++)
			printf("%s\n", data->env[i]);
		printf("i is: %d\n", i);
	}
	if (!ft_strncmp(input, "exit", 4))
	{
		freeData(data);
		exit(0);
	}
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

	printf("Available commands: echo | env | exit.\n");

	handleSignals();

	data = ft_calloc (1, sizeof(t_data));
	initData(data, env);

	start(data);
	freeData(data);
	return (0);
}