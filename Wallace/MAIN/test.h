/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:19:23 by wchow             #+#    #+#             */
/*   Updated: 2024/08/13 04:53:44 by wchow            ###   ########.fr       */
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
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
	char	**env;
	//char	*input;
}	t_data;

//Initialisation
void	initData(t_data *data, char **env);

//Signals
void	handleSignals();
void	ignore_sigquit();
void	resetPrompt(int signum);

//Processing
void	start(t_data *data);
void	process(char *input, t_data *data);

//Exit
void	freeData(t_data *data);

#endif

/* //GNL includes
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

char	*get_next_line(int fd);
char	*store_remainder(char *storage);
char	*ft_line(char *storage, char *line);
void	get_str(char **storage, char *buffer, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free(char **s1, char **s2, char **s3);
int		got_newline(char *storage);
int		ft_strlen2(char *str);

//GNL includes */