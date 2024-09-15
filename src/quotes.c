/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:17:30 by wchow             #+#    #+#             */
/*   Updated: 2024/09/15 22:50:46 by wchow            ###   ########.fr       */
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

Quite complicated, there's a few things to look out for:
	1. Count the quotes, there must be an even number of quotes.
		{Just count quotes and % 2, if != 0 then reject command}
	2. Handling expansion of variables.
	3. Skipping over the quotes is it's own function, but it also returns it's own
	result string. There's also dynamically allocating space for the result string due
	to the nature of expanding variables.
	4. Handling both the expansion AND the skipping of quotes in the original input is
	a lot to fit into a few functions. The problem lies in the variables needing to be
	malloced and used in conjunction with each other.
Ok so expanding varibles work now, just need to implement the actual d_quotes and dynamic
allocation, then concatenating the variable values to the original input.

Actually, why don't I just simply remove the quotes  first
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

char	*expand_variables(char *input, int i, int j, int k)
{
	char	*result;
	char	var_name[1024];
	char	*var_value;
	
	result = malloc(ft_strlen(input) + 1);
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			i++;
			k = 0;
			while (input[i] && ((ft_isalnum(input[i])) || input[i] == '_'))
				var_name[k++] = input[i++];
			var_name[k] = '\0';
			var_value = getenv(var_name);
			if (var_value)
			{
				ft_strlcpy(&result[j], var_value, ft_strlen(var_value) + 1);
				j += ft_strlen(var_value);
			}
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*d_quote(char *input)
{
	char	*result;
	int	inquotes = 0;
	int i = 0, j = 0;

	result = malloc(ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] == '\"')
		{
			inquotes = !inquotes;
			i++;
			continue;
		}
		if (inquotes || input[i] != '\"')
			result[j++] = input[i++];
	}
	result[j] = '\0';
	result = expand_variables(result, 0, 0, 0);
	return (result);
}

/* int	count_quotes(char *input)
{
	int	i;

	i = 0;
	while (*input)
		if (*input == '\'')

} */

char	*ft_quote(char *input)
{
	if (ft_strchr(input, '\''))
	{
		input = s_quote(input);
	}
	if (ft_strchr(input, '\"'))
	{
		input = d_quote(input);
	}
	return (input);
}
