/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:51:00 by wchow             #+#    #+#             */
/*   Updated: 2024/08/13 06:20:31 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	freeData(t_data *data)
{
	int	i;

	i = -1;
	while (++i >= -1 && data->env[i])
		free (data->env[i]);
	free(data->env);
	free(data->path);
	free(data);
}