/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:25:26 by wchow             #+#    #+#             */
/*   Updated: 2023/09/11 16:38:03 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	value;

	str = (unsigned char *) s;
	value = (unsigned char) c;
	while (n--)
	{
		*str = value;
		str++;
	}
	return (s);
}
