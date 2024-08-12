/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:49:52 by wchow             #+#    #+#             */
/*   Updated: 2023/09/11 21:00:49 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*result;
	unsigned char	search;

	result = (unsigned char *) s;
	search = (unsigned char) c;
	while (n--)
	{
		if (*result == search)
			return ((void *)result);
		result++;
	}
	return (0);
}
