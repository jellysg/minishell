/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:03:29 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/10 21:43:31 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char *input, t_data *data)
{
	char *path;
	char *curr_dir;

	// Skip spaces
	path = input + 2;
	while (*path == ' ')
		path++;

	// just "cd" defaults to home
	if (*path == '\0') {
		path = env_value(data->env, "HOME");
		if (!path) {
			ft_printf("cd: Home directory is not set.\n");
			return (FAILURE);
		}
	}
	if (chdir(path) != 0)
	{
		perror("cd error");
		return (FAILURE);
	}
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir) {
		perror("getcwd error");
		return (FAILURE);
	}
	if (data->cwd)
	{
		free(data->cwd);
	}

	// Allocate memory for data->cwd and copy current directory
	data->cwd = ft_strdup(curr_dir);
	if (!data->cwd) {
		perror("ft_strdup error");
		free(curr_dir);
		return (FAILURE);
	}
	free(curr_dir);
    return (SUCCESS);
}