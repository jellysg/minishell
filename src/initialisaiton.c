/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisaiton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:48:38 by wchow             #+#    #+#             */
/*   Updated: 2024/09/30 20:48:18 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    init_struct_ptrs(t_data *d, t_cmd *c, t_pp *p)
{
    d->cwd = "";
    d->path = "";
    d->input = "";
    d->temp = "";
    d->cmd = "";
    d->pid = -1;
    c->command = "";
    c->path = "";
    p->infile = -1;
    p->outfile = -1;
    p->env_path = "";
    p->cmd = "";
    p->here_doc = 0;
    p->pid = -1;
    p->cmd_n = -1;
    p->pipe_n = -1;
    p->idx = -1;
}

int    init_pipe(t_pp *p, t_data *d, int ac, char **av, char **env)
{
	if (ac < args_in(av[1], p))
		return (msg(ERR_INPUT));
	get_infile(av, p);
	get_outfile(av[ac], p);
	p->cmd_n = ac - 2 - p->here_doc;
	p->pipe_n = 2 * (p->cmd_n);
	p->pipe = (int *)malloc(sizeof(int) * p->pipe_n);
	if (!p->pipe)
		perror(ERR_PIPE);
	p->env_path = d->path;
	p->cmd_paths = ft_split(p->env_path, ':');
	if (!p->cmd_paths)
		free_pipe(p);
	create_pipes(p);
	p->idx = -1;
	while (++(p->idx) < p->cmd_n)
		child(p, av, env);
    return (0);
}

void	init_data(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof * data->env);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			data->path = ft_strdup(env[i] + 5);
		i++;
	}
	data->env[i] = NULL;

	// init cwd
	data->cwd = malloc(PATH_MAX);
	if (!data->cwd)
	{
		perror("malloc error");
		exit(FAILURE);
	}

	// set cwd to current dir
	if (getcwd(data->cwd, PATH_MAX) == NULL)
	{
		perror("getcwd error");
		free(data->cwd);
		exit(FAILURE);
	}
}
