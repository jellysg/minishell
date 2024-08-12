/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 03:44:21 by wchow             #+#    #+#             */
/*   Updated: 2023/09/14 04:01:53 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s);
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start < j)
		i = j - start;
	if (i > len)
		i = len;
	substring = malloc(sizeof(char) * (i + 1));
	if (!substring)
		return (0);
	ft_strlcpy(substring, s + start, i + 1);
	return (substring);
}
