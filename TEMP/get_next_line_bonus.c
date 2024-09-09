/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:46:01 by wchow             #+#    #+#             */
/*   Updated: 2024/08/12 11:48:03 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	if (!*str)
		return (0);
	while (*str)
		i++;
	return (i);
}

char	*store_remainder(char *storage)
{
	char	*buffer;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	while (storage[k])
		k++;
	buffer = ft_calloc(k - i + 1, 1);
	if (!buffer)
		return (NULL);
	k = 0;
	while (storage[i + k])
	{
		buffer[k] = storage[i + k];
		k++;
	}
	return (buffer);
}

char	*ft_line(char *storage, char *line)
{
	char	*buffer;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (*storage == '\0')
	{
		ft_free(&line, 0, 0);
		return (NULL);
	}
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	buffer = ft_calloc(i + 1, 1);
	if (!buffer)
		return (NULL);
	while (k < i)
	{
		buffer[k] = storage[k];
		k++;
	}
	buffer[k] = '\0';
	return (buffer);
}

void	get_str(char **storage, char *buffer, int fd)
{
	int		size;
	char	*temp;

	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!temp)
		return ;
	size = 1;
	while (size > 0)
	{
		size = read(fd, temp, BUFFER_SIZE);
		if (size == -1)
		{
			ft_free(storage, &buffer, &temp);
			return ;
		}
		temp[size] = '\0';
		buffer = ft_strdup(*storage);
		ft_free (storage, 0, 0);
		*storage = ft_strjoin(buffer, temp);
		ft_free (&buffer, 0, 0);
		if (got_newline(*storage))
			break ;
	}
	ft_free(&temp, 0, 0);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*buffer;
	char		*line;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	get_str(&storage[fd], buffer, fd);
	if (storage[fd])
	{
		line = ft_line(storage[fd], line);
		buffer = store_remainder(storage[fd]);
		ft_free(&storage[fd], 0, 0);
		storage[fd] = ft_strdup(buffer);
		if (*storage[fd] == '\0')
			ft_free(&storage[fd], 0, 0);
		ft_free(&buffer, 0, 0);
	}
	return (line);
}
