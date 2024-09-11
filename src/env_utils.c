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

// unset var from env
bool	unset_env(t_data *data, int index)
{
	int	i;
	int	count;

	if (index > env_count(data->env))
		return (false);
	free_ptr(data->env[index]);
	i = index;
	count = index;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = calloc_env(data, count);
	if (!data->env)
		return (false);
	return (true);
}

// calloc env, used to init var
char	**calloc_env(t_data *data, int size)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_calloc(sizeof(result), size + 1);
	if (!result)
		return (NULL);
	while (data->env[i] && i < size)
	{
		result[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (result);
}

// adds env var to value
bool	env_set(t_data *data, char *key, char *value)
{
	int		index;
	char	*concat_equals;

	index = env_index(data->env, key);
	if (value == NULL)
		value = "";
	concat_equals = ft_strjoin("=", value);
	if (index != -1 && data->env[index])
	{
		free_ptr(data->env[index]);
		data->env[index] = ft_strjoin(key, concat_equals);
	}
	else
	{
		index = env_count(data->env);
		data->env = calloc_env(data, index + 1);
		if (!data->env)
			return (false);
		data->env[index] = ft_strjoin(key, concat_equals);
	}
	free_ptr(concat_equals);
	return (true);
}

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
bool	valid_env(char *var)
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

// index of the var in the env matching the string
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

// pointer of the var in the env matching the string.
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
