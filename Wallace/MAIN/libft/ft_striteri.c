/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:46:33 by wchow             #+#    #+#             */
/*   Updated: 2023/09/20 15:29:18 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	while (s[len])
		len++;
	while (index < len)
	{
		f(index, &s[index]);
		index++;
	}
}
