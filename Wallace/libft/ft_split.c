/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:57:12 by wchow             #+#    #+#             */
/*   Updated: 2023/09/20 15:27:16 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	num_substr(const char *s, char c)
{
	size_t	nstrs;

	nstrs = 0;
	while (*s)
	{
		if (*s != c)
		{
			nstrs++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (nstrs);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**result;

	i = 0;
	if (!s)
		return (0);
	result = malloc(sizeof(char *) * (num_substr(s, c) + 1));
	if (!result)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			result[i] = ft_substr(s - len, 0, len);
			i++;
		}
		else
			++s;
	}
	result[i] = NULL;
	return (result);
}
