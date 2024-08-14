/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:43:01 by wchow             #+#    #+#             */
/*   Updated: 2023/09/11 19:53:26 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*result;
	unsigned char	*source;

	if (dest == NULL && src == NULL)
		return (dest);
	result = (unsigned char *) dest;
	source = (unsigned char *) src;
	while (n--)
	{
		*result = *source;
		result++;
		source++;
	}
	return (dest);
}
