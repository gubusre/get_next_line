/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:10:46 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/24 18:32:20 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list		*current_fd;
	ssize_t		bytes_read;
	char		*line;
	char		*new_line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = ft_lstfind(&fd_list, fd);
	if (!current_fd)
		return (NULL);
	line = NULL;
	/* manage the rest of already read*/
	if (current_fd->content)
	{
		/* check if in buffer exist "\n" if exist
		 * pointer of new_line have the memory position 
		 * of the "\n" assignet as his memory*/
		new_line = ft_strchr(current_fd->content, '\n');
		/* if new line exist "line jump \n" dupplicate 
		 * from the start until "\n"*/
		if (new_line)
		{
			line = ft_strndup(current_fd->content, 
				new_line - current_fd->content + 1);
			if (!line)
				return (NULL);
			char *tmp = ft_strdup(new_line + 1);
			free(current_fd->content);
			/* assign the current content to the new line 
			 * starting from "\n"*/
			if (!tmp)
			{
				free(line);
				return (NULL);
			}
			current_fd->content = tmp;
			return (line);
		}
		/* if there is no "\n" on the buffer*/
		line = ft_strdup(current_fd->content);
		if (!line)
		{
			free(current_fd->content);
			return (NULL);
		}
		free(current_fd->content);
		current_fd->content = NULL;
	}
	else /* empty content*/
		line = ft_strdup("");
	if (!line)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		if (!line)
		{
			free(buffer);
			free(line);
		}
		return (NULL);
	}
	/*read*/
	while (!(new_line = ft_strchr(line, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		/* in case there is none existing buffer to read 
		 * but we still have a line read from the last buffer
		 * we return the line and then free it and the lst*/
		{
			if (*line)
			{
				current_fd->content = ft_strdup("");
				free(buffer);
				if (line)
				{
					t_list *prev = NULL;
					ft_lstremove(&fd_list, current_fd, prev);
					return (line);
				}
			}
			free(line);
			t_list	*prev = NULL;
			t_list	*temp = fd_list;
			while (temp)
			{
				if (temp->fd == fd)
					break;
				prev = temp;
				temp = temp->next;
			}
			ft_lstremove(&fd_list, temp, prev);
			free(buffer);
			return (NULL);
		}
		/*in case there is an existing buffer we join the buffer
		 * to the "empty line"*/
		buffer[bytes_read] = '\0';
		char	*tmp_join = ft_strjoin(line, buffer);
		if (!tmp_join)
		{
			free(line);
			free(buffer);
			return (NULL);
		}
		free(line);
		line = tmp_join;
	}
	char	*tmp_line = ft_strndup(line, new_line - line + 1);
	if (!tmp_line)
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	char	*tmp_rest = ft_strdup(new_line + 1);
	free(line);
	if (!tmp_rest)
	{
		free(tmp_line);
		free(buffer);
		return (NULL);
	}
	current_fd->content = tmp_rest;
	free(buffer);
	return (tmp_line);
}
