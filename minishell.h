/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:23 by wchow             #+#    #+#             */
/*   Updated: 2024/09/10 20:58:57 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
#include "./libft/libft.h"
#include "./printf/includes/ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

//Macros
# define showCmds "Custom commands: echo | env | exit | showpath\nSystem commands: non-argument syscalls might work e.g. ls | pwd\n"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define SUCCESS 0
# define FAILURE 1

typedef struct s_data
{
	char	**env;
	char	*path;
	char	**args;
	char	*input;
}	t_data;

//Initialisation
void	initData(t_data *data, char **env);
void	set_argv(char *input, char ***argv);

//Signals
void	handleSignals();
void	ignore_sigquit();
void	resetPrompt(int signum);

//Processing
void	start(t_data *data);
void	process(char *input, t_data *data);

//Builtins
void	ft_echo(char *input);
int	checkNewline(char *input);
void	ft_env(t_data *data);
int	ft_exit(t_data *data);
void	free_data(t_data *data, int exit_code);

//Exit
void	freeData(t_data *data);

#endif