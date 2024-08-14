/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:01:27 by wchow             #+#    #+#             */
/*   Updated: 2023/09/13 17:54:02 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dest;
	const char	*source;
	size_t		siz;
	size_t		destlen;

	dest = dst;
	source = src;
	siz = size;
	while (siz-- && *dest)
		dest++;
	destlen = dest - dst;
	siz = size - destlen;
	if (siz == 0)
		return (destlen + ft_strlen(src));
	while (*source)
	{
		if (siz > 1)
		{
			*dest++ = *source;
			siz--;
		}
		source++;
	}
	*dest = '\0';
	return (destlen + (source - src));
}
