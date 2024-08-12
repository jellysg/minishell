/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:46:30 by wchow             #+#    #+#             */
/*   Updated: 2024/08/12 11:46:11 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*s;
	void			*result;
	int				i;

	i = nmemb * size;
	result = (void *)malloc(size * nmemb);
	if (!result)
		return (NULL);
	s = (unsigned char *) result;
	while (i)
	{
		*s++ = 0;
		i--;
	}
	return (result);
}

char	*ft_strdup(const char *s)
{
	int		clen;
	char	*result;
	int		i;

	i = 0;
	clen = 0;
	if (!s)
		return (ft_strdup(""));
	while (s[clen])
		clen++;
	result = ft_calloc((clen + 1), 1);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = ft_calloc((i + j + 1), 1);
	if (!str)
		return (NULL);
	j = -1;
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	return (str);
}

void	ft_free(char **s1, char **s2, char **s3)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 && *s3)
	{
		free(*s3);
		*s3 = NULL;
	}
}

int	got_newline(char *storage)
{
	int	i;

	i = 0;
	while (storage[i])
	{
		if (storage[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
