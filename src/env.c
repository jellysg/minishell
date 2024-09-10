/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:22:29 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 15:22:52 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// free ptr
void    free_ptr(void *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}

// returns the number of env vars.
int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

// true if the only alnum chars or '_', else false.
bool	is_valid_env(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

// index of the variable in the environment matching the string.
int	env_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

// pointer of the variable in the environment matching the string.
char	*env_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}
