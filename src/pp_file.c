/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:22:29 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 15:22:52 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	args_in(char *arg, t_pp *pp)
{
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		pp->here_doc = 1;
		return (6);
	}
	else
	{
		pp->here_doc = 0;
		return (5);
	}
}

void	here_doc(char *argv, t_pp *pp)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		msg_error(ERR_HEREDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);  // Read input from stdin (0) into buf
		if (buf == NULL)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pp->infile = open(".heredoc_tmp", O_RDONLY);
	if (pp->infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_error(ERR_HEREDOC);
	}
}


void	get_infile(char **argv, t_pp *pp)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], pp);
	else
	{
		pp->infile = open(argv[1], O_RDONLY);
		if (pp->infile < 0)
			msg_error(ERR_INFILE);
	}
}

void	get_outfile(char *argv, t_pp *pp)
{
	if (pp->here_doc)
		pp->outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pp->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pp->outfile < 0)
		msg_error(ERR_OUTFILE);
}