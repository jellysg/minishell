/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:23 by wchow             #+#    #+#             */
/*   Updated: 2024/09/30 20:48:01 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <readline/readline.h>
# include <readline/history.h>

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
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_ENVP "Environment"
# define ERR_CMD "Command not found: "
# define ERR_HEREDOC "here_doc"

typedef struct s_data
{
	int	erno;
	char	*temp;
	char	*cwd;
	char	**env;
	char	*path;
	char	**args;
	char	*input;
	char	*cmd;
	pid_t	pid;
	struct s_token	*token;
	struct s_cmd   *cmds;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;

typedef struct s_cmd
{
	char	*command;
	char	*path;
	char	**args;
	struct s_pp *pp;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_pp
{
	int	infile;
	int	outfile;
	char	*env_path;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid;
	int	cmd_n;
	int	pipe_n;
	int	*pipe;
	int	idx;
}	t_pp;

typedef struct s_token
{	
	char	*str;
	char	*str_backup;
	bool	var_exists;
	int	type;
	int	status;
	bool	join;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

enum e_token_types {
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status {
	DEFAULT,
	SQUOTE,
	DQUOTE
};

//Initialisation
void	init_data(t_data *data, char **env);
int	init_pipe(t_pp *p, t_data *d, int ac, char **av, char **env);
void    init_struct_ptrs(t_data *d, t_cmd *c, t_pp *p);

//Signals
void	handle_signals();
void	ignore_sigquit();
void	reset_prompt(int signum);

//Parsing
bool	parse_user_input(t_data *data);

//Tokenization
int	save_sep(t_token **token_lst, char *str, int index, int type);
int	save_word(t_token **token_lst, char *str, int index, int start);
int	is_sep(char *str, int i);
int	set_status(int status, char *str, int i);
int	save_word_or_sep(int *i, char *str, int start, t_data *data);
int	tokenization(t_data *data, char *str);
t_token	*lst_new_token(char *str, char *str_backup, int type, int status);
void	lst_add_back_token(t_token **alst, t_token *new_node);
void	lstdelone_token(t_token *lst, void (*del)(void *));
void	lstclear_token(t_token **lst, void (*del)(void *));
t_token	*insert_lst_between(t_token **head, t_token *to_del, t_token *insert);

//Pipes
void	child(t_pp *p, char **argv, char **envp);
int	args_in(char *arg, t_pp *pp);
void	here_doc(char *argv, t_pp *pp);
int	get_infile(char **argv, t_pp *pp);
void	get_outfile(char *argv, t_pp *pp);
void	create_pipes(t_pp *pipe);
void	close_pipes(t_pp *pipe);
void	free_parent(t_pp *p);
void	free_child(t_pp *p);
void	free_pipe(t_pp *p);
int	msg(char *err);
void	msg_pipe(char *arg);

//Env utils
bool	unset_env(t_data *data, int index);
char	**calloc_env(t_data *data, int size);
bool	env_set(t_data *data, char *key, char *value);
void    free_ptr(void *ptr);
int	env_count(char **env);
bool	valid_env(char *var);
int	env_index(char **env, char *var);
char	*env_value(char **env, char *var);

//Sys call
void	set_argv(char *input, char ***argv, t_data *data);
void	ft_fork_and_exec(t_data *data, char *input, char **argv);
void	sys_call(char *input, t_data *data);

//Processing
void	start(t_data *data, t_pp *p);
int	process(char *input, t_data *data, t_pp *p);

//Quotes
char	*ft_quote(char *input, int i, int j, t_data *data);

//Builtins
int	ft_cd(char *input, t_data *data);
int	ft_echo(t_data *data);
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
void	exit_shell(t_data *data, int exno);

#endif