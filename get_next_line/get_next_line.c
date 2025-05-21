/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:52:34 by gubusque          #+#    #+#             */
/*   Updated: 2025/05/21 23:01:51 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*appended_buffer(char *current_res, char *read_buf)
{
	char	*new_res;

	if (!current_res)
	{
		new_res = ft_strdup(read_buf);
		if (!new_res)
			return (NULL);
		return (new_res);
	}
	new_res = ft_strjoin(current_res, read_buf);
	if (!new_res)
		return (free(current_res), NULL);
	free(current_res);
	return (new_res);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer && res)
		return (free(res), NULL);
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (!(res && ft_strchr(res, '\n')) && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1 && res)
			free(res);
		if (byte_read == -1)
			return (free(buffer), NULL);
		buffer[byte_read] = '\0';
		res = appended_buffer(res, buffer);
		if (!res)
			return (free(buffer), NULL);
	}
	if (byte_read == 0 && !res)
		return (free(buffer), NULL);
	return (free(buffer), res);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;
	int		alloc_size;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	alloc_size = i + 1;
	if (buffer[i] == '\n')
		alloc_size++;
	line = (char *)ft_calloc(alloc_size, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = buffer[i];
	return (line);
}

char	*ft_next(char *buffer)
{
	char	*remainder;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), NULL);
	j = ft_strlen(buffer);
	remainder = (char *)ft_calloc((j - i) + 1, sizeof(char));
	if (!remainder)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < MAX_FD && buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}
