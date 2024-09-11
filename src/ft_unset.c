/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:12:12 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/12 03:58:09 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **argv, t_data *data)
{
	int	i;
	int	index;
	int	result;

	i = 1;
	result = SUCCESS;
	while (argv[i])
	{
		if (!valid_env(argv[i]) || ft_strchr(argv[i], '=') != NULL)
			result = FAILURE;
		else
		{
			index = env_index(data->env, argv[i]);
			if (index != -1)
				unset_env(data, index);
		}
		i++;
	}
	return (result);
}