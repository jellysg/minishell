/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisaiton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:48:38 by wchow             #+#    #+#             */
/*   Updated: 2024/09/10 17:38:12 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initData(t_data *data, char **env)
{
	int i = 0;
	while (env[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof * data->env);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			data->path = ft_strdup(env[i] + 5);
			break;
		}
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