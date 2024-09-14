/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:17:30 by wchow             #+#    #+#             */
/*   Updated: 2024/09/14 14:32:51 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Single quotes: Escape the entire sequence within single quotes so that no special 
characters are interpreted. If you encounter a single quote, keep reading the input 
until the closing single quote and treat everything in between as literal. */

/* The result of {echo '1'2 'Hello world'''} is {12 Hello World}. This implies that the way
quotes are handled is by directly removing the single quotes while saving the previous
characters BEFORE meeting the single quotes. Substring everytime it detects squote?*/

/* Double quotes: Handle most characters literally, except:
Expand $ to substitute variables.
Allow command substitution with backticks ` (optional, depending on project requirements).
*/ 

#include "../minishell.h"

/* char	*ft_strtrim_once(char const *s1, char const *set)
{
	size_t	startlen;
	size_t	endlen;

	startlen = 0;
	endlen = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (0);
	if (s1[startlen] && ft_strchr(set, s1[startlen]))
		startlen++;
	if (endlen > startlen && ft_strchr(set, s1[endlen]))
		endlen--;
	return (ft_substr(s1, startlen, endlen - startlen + 1));
} */

char	*s_quote(char *input)
{
	char	*result;
	int	inquotes = 0;
	int i = 0, j = 0;

	result = malloc(ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] == '\'')
		{
			inquotes = !inquotes;
			i++;
			continue;
		}
		if (inquotes || input[i] != '\'')
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_quote(char *input)
{
	if (ft_strchr(input, '\''))
	{
		input = s_quote(input);
	}
	return (input);
}
