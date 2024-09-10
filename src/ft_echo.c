/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:44:06 by wchow             #+#    #+#             */
/*   Updated: 2024/09/10 21:27:07 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Checks whether input has -n or not, then sends it to the main echo function */
int	checkNewline(char *input)
{
	//If there is a -n, means FORGO \n at the back
	if (!ft_strncmp(input, "-n ", 3))
		return (0);
	else
		return (1);
}

/* Custom echo command. If (newline == 1) = no -n. If (newline == 0) = there is -n. */
void	ft_echo(char *input)
{
	int	newline;

	newline = checkNewline(input);
	if (newline == 1)
		ft_printf("%s\n", input);
	else
		ft_printf("%s", input + 3);
}