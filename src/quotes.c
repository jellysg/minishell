/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:17:30 by wchow             #+#    #+#             */
/*   Updated: 2024/09/18 16:34:10 by wchow            ###   ########.fr       */
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

18/9/24
Finished handling both single and double quotes. Squotes will ignore everything and send
result as is, while dquotes will take in $ and ". 
This is to facilitate echo not needingto change the code cos now it's using ft_quote to 
check for everything then print it; meaning now echo $USER works without needing to be
in quotes like echo "$USER" anymore.
	This is done by checking the first character it meets that is either quotes or $,
	so hopefully it doesn't run into any weird edge cases.

TODO: Try to allow other commands other than echo to use quotes (implement in argv or
during process? Idk yet)
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

/* char	*s_quote(char *input)
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

int	has_matching_quotes(char *input, int s_quotes, int d_quotes, int i)
{
	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		if (input[i] == '\"' && s_quotes % 2 == 0)
			d_quotes++;
		i++;
	}
	if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
	{
		if (s_quotes % 2 != 0)
			ft_printf("unexpected EOF while looking for matching `''\n");
		else if (d_quotes % 2 != 0)
			ft_printf("unexpected EOF while looking for matching `\"'\n");
		return (1);
	}
	return (0);
}

char	*ft_quote(char *input)
{
	if (has_matching_quotes(input, 0, 0, 0) != 0)
		return (0);
	if (ft_strchr(input, '\''))
	{
		input = s_quote(input);
	}
	if (ft_strchr(input, '\"'))
	{
		input = d_quote(input);
	}
	return (input);
} */

char	*s_quote(char *input, int *i)
{
	int	j;
	char	*result;

	j = 0;
	result = malloc(ft_strlen(input) + 1);
	(*i)++;  // Skip the initial single quote
	while (input[*i] && input[*i] != '\'')
	{
		result[j++] = input[*i];
		(*i)++;
	}
	(*i)++;  // Skip the closing single quote
	result[j] = '\0';
	return (result);
}

void	expand_variables(char **result, char *input, int *i, int *j)
{
	char	var_name[1024];
	char	*var_value;
	int	k;

	(*i)++;  // Skip the '$'
	k = 0;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		var_name[k++] = input[(*i)++];
	var_name[k] = '\0';
	var_value = getenv(var_name);
	if (var_value)
	{
		if (!result)
			*result = ft_strdup(var_value);
		else
			*result = ft_strjoin(*result, var_value);
		*j += ft_strlen(var_value);
	}
}

char	*d_quote(char *input, int *i)
{
	char	*result;
	int	j;

	j = 0;
	result = malloc(ft_strlen(input) + 1);
	ft_bzero(result, ft_strlen(input) + 1);
	if (input[*i] == '\"')
		(*i)++;  // Skip the opening double quote
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$')  // Expand variables inside double quotes
			expand_variables(&result, input, i, &j);
		else
		{
			result[j++] = input[*i];
			(*i)++;
		}
	}
	(*i)++;  // Skip the closing double quote
	result[j] = '\0';
	return (result);
}

int	has_matching_quotes(char *input)
{
	int s_quotes = 0;
	int d_quotes = 0;
	int i = 0;

	while (input[i])
	{
		if (input[i] == '\'' && d_quotes % 2 == 0)
			s_quotes++;
		else if (input[i] == '\"' && s_quotes % 2 == 0)
			d_quotes++;
		i++;
	}
	if (s_quotes % 2 != 0 || d_quotes % 2 != 0)
	{
		if (s_quotes % 2 != 0)
			ft_printf("unexpected EOF while looking for matching `''\n");
		else if (d_quotes % 2 != 0)
			ft_printf("unexpected EOF while looking for matching `\"'\n");
		return (1);
	}
	return (0);
}

char	*ft_quote(char *input, int i, int j)
{
	char	*quoted_str;
	char	*result;

	if (has_matching_quotes(input) != 0)
		return (0);
	result = malloc(ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"' || input[i] == '$')
		{
			if (input[i] == '\'')
				quoted_str = s_quote(input, &i);  // Pass the pointer to modify i
			else if (input[i] == '\"' || input[i] == '$')
				quoted_str = d_quote(input, &i);  // Pass the pointer to modify i
			ft_strlcpy(&result[j], quoted_str, ft_strlen(quoted_str) + 1);
			j += ft_strlen(quoted_str);
			free(quoted_str);
		}
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}