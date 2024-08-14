/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisaiton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:48:38 by wchow             #+#    #+#             */
/*   Updated: 2024/08/13 06:18:58 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	initData(t_data *data, char **env)
{
	int i = 0;
	while (env[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof * data->env);
	for (i = 0; env[i]; i++)
	{
		data->env[i] = ft_strdup(env[i]);
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			data->path = ft_strdup(env[i] + 5);
			break;
		}
	}
	data->env[i] = NULL;
}