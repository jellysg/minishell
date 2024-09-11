/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:00:12 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/11 21:01:02 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	how to test export functionality:
	1. env
	2. export test=
	3. env
	4. export test=variable
	5. env
	6. printenv test
*/

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i])
			{
				free_ptr(str[i]);
				str[i] = NULL;
			}
			i++;
		}
		free(str);
		str = NULL;
	}
}

char	**defined_var(char *arg)
{
	char	*equals_index;
	char	**result;

	equals_index = ft_strchr(arg, '=');
	result = malloc(sizeof(result) * 3);
	result[0] = ft_substr(arg, 0, equals_index - arg);
	result[1] = ft_substr(equals_index, 1, ft_strlen(equals_index));
	result[2] = NULL;
	return (result);
}

int	ft_export(char **argv, t_data *data)
{
	int	i;
	int	result;
	char **var_value;

	i = 1;
	result = SUCCESS;
	if (!argv[1])
		return(FAILURE);
	while (argv[i])
	{
		if (!valid_env(argv[i]))
			return(FAILURE);
		else if (ft_strchr(argv[i], '='))
		{
			var_value = defined_var(argv[i]);
			env_set(data, var_value[0], var_value[1]);
			free_array(var_value);
		}
		i++;
	}
	return (result);
}