/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:22:29 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 15:22:52 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(t_pp *pp)
{
	int	i;

	i = 0;
	while (i < pp->cmd_n - 1)
	{
		if (pipe(pp->pipe + 2 * i) < 0)
			free_parent(pp);
		i++;
	}
}

void	close_pipes(t_pp *pp)
{
	int	i;

	i = 0;
	while (i < (pp->pipe_n))
	{
		close(pp->pipe[i]);
		i++;
	}
}