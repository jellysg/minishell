/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 02:46:38 by wchow             #+#    #+#             */
/*   Updated: 2023/09/24 02:49:20 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		pf_putstr("(null)");
		return (6);
	}
	while (*s)
	{
		write (1, s, 1);
		count++;
		s++;
	}
	return (count);
}

int	pf_putnbr(int n)
{
	char	result;
	int		count;

	count = 0;
	if (n <= -2147483648)
	{
		count += pf_putstr ("-2147483648");
		return (count);
	}
	if (n < 0)
	{
		write (1, "-", 1);
		count++;
		n = -n;
	}
	if (n > 9)
		count += pf_putnbr (n / 10);
	result = (n % 10) + '0';
	count += write (1, &result, 1);
	return (count);
}

int	pf_uputnbr(unsigned int n)
{
	char	result;
	int		count;

	count = 0;
	if (n > 9)
		count += pf_uputnbr(n / 10);
	result = (n % 10) + '0';
	count += write(1, &result, 1);
	return (count);
}

int	pf_hexadd_util(unsigned long long ptr)
{
	char	result;
	int		count;

	if (ptr < 16)
	{
		result = "0123456789abcdef"[ptr % 16];
		write(1, &result, 1);
		return (1);
	}
	result = "0123456789abcdef"[ptr % 16];
	count = pf_hexadd_util(ptr / 16);
	write(1, &result, 1);
	return (count + 1);
}

int	pf_printhex(unsigned int n, const char *base)
{
	int	count;

	count = 0;
	if (n < 16)
	{
		write(1, &base[n], 1);
		return (1);
	}
	count = pf_printhex(n / 16, base);
	write(1, &base[n % 16], 1);
	return (count + 1);
}
