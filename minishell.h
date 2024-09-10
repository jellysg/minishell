/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:23 by wchow             #+#    #+#             */
/*   Updated: 2024/09/10 17:40:25 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define SUCCESS 0
# define FAILURE 1

typedef struct s_data
{
	char	*cwd;
	char	**env;
	char	*path;
	char	**args;
	//char	*input;
}	t_data;

//Initialisation
void	initData(t_data *data, char **env);

//Signals
void	handleSignals();
void	ignore_sigquit();
void	resetPrompt(int signum);

//Env
void    free_ptr(void *ptr);
int	env_count(char **env);
bool	is_valid_env(char *var);
int	env_index(char **env, char *var);
char	*env_value(char **env, char *var);

//Processing
void	start(t_data *data);
void	process(char *input, t_data *data);

//Builtins
void	ft_cd(char *input, t_data *data);
void	ft_echo(char *input);
int	checkNewline(char *input);

//Exit
void	freeData(t_data *data);

#endif