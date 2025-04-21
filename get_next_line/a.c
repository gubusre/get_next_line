/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:22:28 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/21 20:10:42 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strjoin_len(char *content, char *buffer, size_t len)
{
	char	*mod_content;
	size_t	content_len;
	size_t	i;
	size_t	j;

	content_len = ft_strlen(content);
	mod_content = malloc(sizeof(char) * (content_len + len));
	if (!mod_content)
		return (NULL);
	i = 0;
	while(content[i] != '\0')
	{
		mod_content[i] = content[i];
		i++;
	}
	j = 0;
	while(buffer[j] != '\0')
	{
		mod_content[i + j] = buffer[j];
		j++;
	}
	mod_content[i + j] = '\0';
	return (mode_content);

}




char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list		*current_fd;
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];
	char		*current_line;
	char		*new_line;

	read(fd, buffer, BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE || read(fd, buffer, 0) < 0)
		return (NULL);
	current_fd = ft_lstfind
	while (buffer[i] != '\n' || buffer[i] != '\0')
	{
		i++;
		line_len++;
	}
	if (buffer[i] != '\n' || buffer[i] != '\0')
		line_len = 0;
	ft_strjoin_len(dst, buffer, line_len); //modify strjoin)
	new_node =
	i = 0;

	while (buffer[i])
}

t_list  *ft_lstnew(void *content)
{
        t_list  *new_node;

        if (!content)
                return (NULL);
        new_node = (t_list *)malloc(sizeof(t_list));
        if(!new_node)
                return (NULL);
        new_node->content = content;
        new_node->next = NULL;
        return (new_node);
}

