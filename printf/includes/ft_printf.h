/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:41:21 by wchow             #+#    #+#             */
/*   Updated: 2023/09/13 21:20:23 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_checkconv(const char *str, va_list args);
int	pf_putstr(char *s);
int	pf_putnbr(int n);
int	pf_uputnbr(unsigned int n);
int	pf_hexadd(void *ptr);
int	pf_hexadd_util(unsigned long long ptr);
int	pf_printhex(unsigned int n, const char *base);

#endif
