/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:10:46 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/21 22:28:56 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef strcut s_list
{
	char	*content;
	int	fd;
	struct s_list *next;
}	t_list;

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

t_list	*ft_lstnew(int fd)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = NULL;
	new_node->fd = fd;
	new_node->next = NULL;
	return (new_node);
}

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
	if !(new_node)
		return (NULL);
	ft_lstadd_front(lst, new_node);
	return (new_node);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list		*currend_fd;
	ssize_t		bytes_read;
	char		*line;
	char		*new_line;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < o || BUFFER_SIZE <= || read(fd, buff, 0) < 0)
		return (NULL);
	current_fd = ft_lstfind(&fd_list, fd);
	if (!current_fd)
		return (NULL);
	/* manage the rest of a baked read*/
	if (current_fd->content)
	{
		new_line = ft_strchr(current_fd->content, '\n'); // make ft_strchr 
		if (new_line)
		{
			line = strndup(current_fd->content, new_line - current_fd->content + 1); //make ft_strndup etc
			char *tmp = ft_strdup(new_line + 1); // make ft_strdup and var tmp
			free(current_fd->content);
			current_fd->content = tmp;
			return (line);
		}
		line = ft_strdup(current_fd->content);
		free(current_fd->content);
		current_fd->content = NULL;
	}
	else
		line = strdup("");
}
