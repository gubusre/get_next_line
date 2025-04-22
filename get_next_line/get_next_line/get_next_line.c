/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:10:46 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/22 20:06:32 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstfind(t_list **lst, int fd)
{
	t_list	*new_node;
	t_list	*current;

	/*if list not exist create a new list and the **lst 
	 * will be pointing the first node of the list*/
	if (!lst || !*lst)
	{
		new_node = ft_lstnew(fd);
		if (!new_node)
			return (NULL);
		ft_lstadd_front(lst, new_node);
		return (new_node);
	}
	/*if the list exist iterate the list until find 
	 * the node with the same current file descriptor*/
	current = *lst;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	/* if not found the create a new list
	 * with the fd being read and ad it to
	 * the first pointer of the list*/
	new_node = ft_lstnew(fd);
	if (!(new_node))
		return (NULL);
	ft_lstadd_front(lst, new_node);
	return (new_node);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list		*current_fd;
	ssize_t		bytes_read;
	char		*line;
	char		*new_line;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (NULL);
	current_fd = ft_lstfind(&fd_list, fd);
	if (!current_fd)
		return (NULL);
	/* manage the rest of already read*/
	if (current_fd->content)
	{
		//printf("current_fd->content = %s\n", current_fd->content); //"aaaaaa"
		/* check if in buffer exist "\n" if exist
		 * pointer of new_line have the memory position 
		 * of the "\n" assignet as his memory*/
		new_line = ft_strchr(current_fd->content, '\n');
		/* if new line exist "line jump \n" dupplicate 
		 * from the start until "\n"*/
		if (new_line)
		{
			line = strndup(current_fd->content, 
				new_line - current_fd->content + 1);	
			//printf("line inside new line = %s\n", line); //"aaaaaaaaaaaa"
			char *tmp = ft_strdup(new_line + 1);
			free(current_fd->content);
			/* assign the current content to the new line 
			 * starting from "\n"*/
			current_fd->content = tmp;
			return (line);
		}
		/* if there is no "\n" on the buffer*/
		line = ft_strdup(current_fd->content);
		//printf("line before free = %s\n", line); //"aaaaaaaaaaaaaaaaaaaaaaaa"
		free(current_fd->content);
		current_fd->content = NULL;
	}
	else /* empty content*/
		line = strdup("");
	//printf("assigning empty line or existing  = %s\n", line); //"aaaaaaaaaaaaaa"
	/*read*/
	while (!(new_line = strchr(line, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//printf("bytes read = %zd\n", bytes_read); //"aaaaaaaaaaaaaa"
		if (bytes_read <= 0)
		/* in case there is none existing buffer to read 
		 * but we still have a line read from the last buffer
		 * we return the line and then free it and the lst*/
		{
			if (*line)
				return (line);
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
			return (NULL);
		}
		/*in case there is an existing buffer we join the buffer
		 * to the "empty line"*/
		buffer[bytes_read] = '\0';
		//printf("line bf join = %s\n", line); //"aaaaaaaaaaaaaaaaaaaaaaa"
		//printf("buffer = %s\n", buffer); //"aaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
		char	*tmp_join = ft_strjoin(line, buffer);
		//printf("tmp_join  = %s\n", tmp_join); //"aaaaaaaaaaaaaaaaaaaaaaaa"
		free(line);
		line = tmp_join;
	}
	//printf("line before free 0 = %s\n", line); //"aaaaaaaaaaaaaaaaaaaaaaaa"
	char	*tmp_line = ft_strndup(line, new_line - line + 1);
	char	*tmp_rest = strdup(new_line + 1);
	free(line);
	current_fd->content = tmp_rest;
	//printf("line before free 1 = %s\n", tmp_line); //"aaaaaaaaaaaaaaaaaaaaaaa"
	return (tmp_line);
}
