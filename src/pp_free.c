/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:22:29 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 15:22:52 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_parent(t_pp *p)
{
	int	i;

	i = 0;
	close(p->infile);
	close(p->outfile);
	if (p->here_doc)
		unlink(".heredoc_tmp");
	while (p->cmd_paths && p->cmd_paths[i])
	{
		free(p->cmd_paths[i]);
		i++;
	}
	free(p->cmd_paths);
	free(p->pipe);
}

void	free_child(t_pp *p)
{
	int	i;

	i = 0;
	while (p->cmd_args[i])
	{
		free(p->cmd_args[i]);
		i++;
	}
	free(p->cmd_args);
	free(p->cmd);
}

void	free_pipe(t_pp *p)
{
	close(p->infile);
	close(p->outfile);
	if (p->here_doc)
		unlink(".heredoc_tmp");
	free(p->pipe);
	msg(ERR_ENVP);
	exit(1);
}