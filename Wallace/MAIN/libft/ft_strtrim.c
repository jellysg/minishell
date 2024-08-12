/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 05:27:26 by wchow             #+#    #+#             */
/*   Updated: 2023/09/14 05:49:27 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	startlen;
	size_t	endlen;

	startlen = 0;
	endlen = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (0);
	while (s1[startlen] && ft_strchr(set, s1[startlen]))
		startlen++;
	while (endlen > startlen && ft_strchr(set, s1[endlen]))
		endlen--;
	return (ft_substr(s1, startlen, endlen - startlen + 1));
}
