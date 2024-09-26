/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergoh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:12:12 by jergoh            #+#    #+#             */
/*   Updated: 2024/09/12 03:58:09 by jergoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

static bool	input_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_user_input(t_data *data)
{
	if (data->input == NULL)
		return (false);
	else if (input_space(data->input))
		return (true);
	add_history(data->input); // Add to history if input is not empty
	if (tokenization(data, data->input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	return (true);
}