/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 08:52:40 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/20 21:31:11 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	reinit_io(t_io *io)
{
	int	result;

	result = true;
	if (!io)
		return (result);
	if (io->stdin_temp != -1)
	{
		if (dup2(io->stdin_temp, STDIN_FILENO) == -1)
			result = false;
		close(io->stdin_temp);
		io->stdin_temp = -1;
	}
	if (io->stdin_temp != -1)
	{
		if (dup2(io->stdin_temp, STDOUT_FILENO) == -1)
			result = false;
		close(io->stdin_temp);
		io->stdin_temp = -1;
	}
	return (result);
}

bool	redir_io(t_io *io)
{
	int	result;

	result = true;
	if (!io)
		return (result);
	io->stdin_temp = dup(STDIN_FILENO);
	if (io->stdin_temp == -1)
		result = false;
	io->stdin_temp = dup(STDOUT_FILENO);
	if (io->stdin_temp == -1)
		result = false;
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			result = false;
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			result = false;
	return (result);
}

bool	check_io(t_io *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1) || (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}

void	init_io(t_cmd *c)
{
	if (!c->io_fd)
	{
		c->io_fd = malloc(sizeof * c->io_fd);
		if (!c->io_fd)
			return ;
		c->io_fd->infile = NULL;
		c->io_fd->outfile = NULL;
		c->io_fd->heredoc_delimiter = NULL;
		c->io_fd->heredoc_quotes = false;
		c->io_fd->fd_in = -1;
		c->io_fd->fd_out = -1;
		c->io_fd->stdin_temp = -1;
		c->io_fd->stdout_temp = -1;
	}
}

void	close_pipes(t_cmd *c, t_cmd *c_temp)
{
	while (c)
	{
		if (c != c_temp && c->pipe_fd)
		{
			close(c->pipe_fd[0]);
			close(c->pipe_fd[1]);
		}
		c = c->next;
	}
}

bool	malloc_pipes(t_data *data)
{
	int			*fd;
	t_cmd	*temp;

	temp = data->cmds;
	while (temp)
	{
		if (temp->pipe_out || (temp->prev && temp->prev->pipe_out))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			temp->pipe_fd = fd;
		}
		temp = temp->next;
	}
	return (true);
}

bool	init_pipes(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_out)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
	if (c->pipe_out)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipes(cmds, c);
	return (true);
}