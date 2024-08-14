/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:03:02 by wchow             #+#    #+#             */
/*   Updated: 2023/09/11 20:40:02 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*result;
	unsigned char	*source;
	unsigned char	*temp;

	result = (unsigned char *) dest;
	source = (unsigned char *) src;
	temp = (unsigned char *) src;
	if (dest == src || n == 0)
		return (dest);
	if (dest < src && dest + n > src)
	{
		temp = result;
		while (n--)
			*temp++ = *source++;
	}
	else
	{
		temp = result + n;
		source += n;
		while (n--)
			*(--temp) = *(--source);
	}
	return (dest);
}
