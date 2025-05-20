/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:52:34 by gubusque          #+#    #+#             */
/*   Updated: 2025/05/19 19:47:03 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*appended_buffer(char *current_res, char *read_buf)
{
	char	*new_res;

	if (!current_res)
	{
		new_res =ft_strdup(read_buf);
		if (!new_res)
			return (NULL);
		return (new_res);
	}
	new_res = ft_free(current_res, read_buf);
	if (!new_res)
		return (NULL);
	return (new_res);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		if (res)
			free(res);
		return (NULL);
	}
	byte_read = 1;
	while (!(res && ft_strchr(res, '\n')) && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			if (res)
				free(res);
			return (NULL);
		}
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		res = appended_buffer(res, buffer);
		if (!res)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	if (byte_read == 0 && !res)
		return (NULL);
	return (res);
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
	line = ft_calloc(alloc_size, sizeof(char));
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
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	len = ft_strlen(buffer);
	remainder = ft_calloc((len - i), sizeof(char));
	if (!remainder)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		remainder[j++] = buffer[i++];
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
