/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:11:21 by wchow             #+#    #+#             */
/*   Updated: 2024/09/11 19:59:46 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_data *data)
{
	int	i;

	if (data->args && data->args[1])
		printf("Invalid. Too many arguments\n");
	else
	{
		i = 0;
		while (data->env[i])
		{
			printf("%s\n", data->env[i]);
			i++;
		}
	}
    return (SUCCESS);
}