/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:23:17 by wchow             #+#    #+#             */
/*   Updated: 2023/09/11 21:35:25 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		clen;
	char	*result;
	int		i;

	i = 0;
	clen = 0;
	while (s[clen])
		clen++;
	result = malloc(sizeof(char) * (clen + 1));
	if (!result)
		return (NULL);
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
