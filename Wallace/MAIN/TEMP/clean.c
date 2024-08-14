/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:05 by wchow             #+#    #+#             */
/*   Updated: 2024/08/12 13:00:15 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	resetPrompt(int signum)
{
	(void)signum;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

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
}

void	initData(t_data *data, char **env)
{
	int i = 0;
	while (env[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof * data->env);
	for (i = 0; env[i]; i++)
		data->env[i] = ft_strdup(env[i]);
	data->env[i] = NULL;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	struct sigaction	sa;
	t_data	*data;
	char	*input;
	printf("Only use echo or env for now.\n");

	//Signal handling and removing CTL+C (need to add CTRL+/)
	ignore_sigquit();
	sa.sa_handler = &resetPrompt; //Gives prompt to usr and waits for input
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	data = ft_calloc (1, sizeof(t_data));
	initData(data, env);
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
	return (0);
}