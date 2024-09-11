/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:03:11 by wchow             #+#    #+#             */
/*   Updated: 2024/09/11 20:31:54 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data *data)
{
	if (data->cwd)
		free (data->cwd);
	data->cwd = malloc(PATH_MAX);
	if (!getcwd(data->cwd, PATH_MAX))
	{
		perror("getcwd failed.");
		free(data->cwd);
		return (FAILURE);
	}
	printf("%s\n", data->cwd);
	return (SUCCESS);
}
