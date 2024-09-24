/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 11:32:12 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/24 15:20:01 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_pp *p, char **argv, char **envp)
{
	p->pid = fork();
	if (!p->pid)
	{
		if (p->idx == 0)
			sub_dup2(p->infile, p->pipe[1]);
		else if (p->idx == p->cmd_n - 1)
			sub_dup2(p->pipe[2 * p->idx - 2], p->outfile);
		else
			sub_dup2(p->pipe[2 * p->idx - 2], p->pipe[2 * p->idx + 1]);
		close_pipes(p);
		p->cmd_args = ft_split(argv[2 + p->here_doc + p->idx], ' ');
		p->cmd = get_cmd(p->cmd_paths, p->cmd_args[0]);
		if (!p->cmd)
		{
			msg_pipe(p->cmd_args[0]);
			free_child(p);
			exit(1);
		}
		execve(p->cmd, p->cmd_args, envp);
	}
}