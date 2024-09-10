/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:11:22 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 17:11:23 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_data(t_data *data, int exit_code)
{
	int	i;

	i = -1;
	while (++i >= -1 && data->env[i])
		free (data->env[i]);
	i = -1;
	while (++i >= -1 && data->args[i])
		free (data->args[i]);
	free(data->env);
	free(data->path);
	free(data->input);
	free(data->args);
	free(data);
	exit(exit_code);
}

int	ft_exit(t_data *data)
{
	printf("exit\n");
	if (data->args[1] && data->args[2])
	{
		printf("Invalid. Too many arguments\n");
		return (1);
	}
	else if (data->args[1] != NULL)
	{
		if (!ft_isdigit(data->args[1][0]))
		{
			printf("Invalid. Input numerical value\n");
			return (1);
		}
		else 
			free_data(data, ft_atoi(data->args[1]));
	}
	exit(0);
	return (0);
}