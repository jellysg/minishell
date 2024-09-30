/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:44:06 by wchow             #+#    #+#             */
/*   Updated: 2024/09/30 20:53:03 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Checks whether input has -n or not, then sends it to the main echo function */
int	checkNewline(char *input)
{
	//If there is a -n, means FORGO \n at the back
	if (input && !ft_strncmp(input, "-n ", 3))
		return (0);
	else
		return (1);
}

/* Custom echo command. If (newline == 1) = no -n. If (newline == 0) = there is -n. */
int	ft_echo(t_data *data)
{
	int	newline;

	newline = checkNewline(data->args[1]);
	if (newline == 1)
	{
		if (ft_quote(data->input + 5, 0, 0, data))
			ft_printf("%s\n", ft_quote(data->input + 5, 0, 0, data));
	}
	else
	{
		if (ft_quote(data->input + 5, 0, 0, data))
			ft_printf("%s", ft_quote(data->input + 8, 0, 0, data));
	}
	return (SUCCESS);
}
//echo Hello world "User is: $USER | Shell is: $SHELL" '$USER $SHELL' End