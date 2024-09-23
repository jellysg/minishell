/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:23 by wchow             #+#    #+#             */
/*   Updated: 2024/09/18 14:59:27 by wchow            ###   ########.fr       */
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
#include <errno.h>
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
	char	*input;
	char	*cmd;
	char	*pipe_fd;
	char	*pipe_out;
	pid_t	pid;
    struct  s_cmd   *cmds;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;

typedef struct s_cmd
{
	char	*command;
	char	*path;
	char	**args;
	bool	pipe_out;
	int		*pipe_fd;
	struct s_io	*io_fd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_io
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_temp;
	int		stdout_temp;
}	t_io;

//Initialisation
void	initData(t_data *data, char **env);
void	set_argv(char *input, char ***argv);

//Signals
void	handleSignals();
void	ignore_sigquit();
void	resetPrompt(int signum);

//Env utils
bool	unset_env(t_data *data, int index);
char	**calloc_env(t_data *data, int size);
bool	env_set(t_data *data, char *key, char *value);
void    free_ptr(void *ptr);
int	env_count(char **env);
bool	valid_env(char *var);
int	env_index(char **env, char *var);
char	*env_value(char **env, char *var);

//Processing
void	start(t_data *data, t_cmd *c);
int	process(char *input, t_data *data);

//Quotes
char	*ft_quote(char *input, int i, int j);

//Pipe and Redir
bool	reinit_io(t_io *io);
bool	redir_io(t_io *io);
bool	check_io(t_io *io);
void	init_io(t_cmd *c);
void	close_pipes(t_cmd *c, t_cmd *c_temp);
bool	malloc_pipes(t_data *data);
bool	init_pipes(t_cmd *cmd, t_cmd *c);
//Pipe and Redir (in main.c)
void	close_fds(t_cmd *cmd, bool check);
int	get_child(t_data *data, t_cmd *cmd);
int	init_child(t_data *data, t_cmd *cmd);
int	prep_exec(t_data *data, t_cmd *cmd);
int	execute(t_data *data, t_cmd *cmd);

//Builtins
int	ft_cd(char *input, t_data *data);
int	ft_echo(char *input);
int	checkNewline(char *input);
int	ft_env(t_data *data);
int	ft_pwd(t_data *data);
int	ft_exit(t_data *data, bool ctrl_d);
void	free_data(t_data *data, int exit_code);
void	free_array(char **str);
char	**defined_var(char *arg);
int	ft_export(char **argv, t_data *data);
int	ft_unset(char **argv, t_data *data);

//Exit
void	freeData(t_data *data);

#endif