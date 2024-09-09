/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:55:59 by wchow             #+#    #+#             */
/*   Updated: 2023/09/20 15:25:52 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_countn(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	num;
	unsigned int	len;

	len = ft_countn(n);
	result = malloc(len + 1);
	if (!result)
		return (0);
	if (n < 0)
	{
		num = -n;
		result[0] = '-';
	}
	else
		num = n;
	if (num == 0)
		result[0] = '0';
	result[len] = '\0';
	while (num != 0)
	{
		len--;
		result[len] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}
