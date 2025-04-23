/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:47:53 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/23 22:26:30 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(int	fd)
{
	t_list	*new_node;

	if (fd < 0)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if(!new_node)
		return (NULL);
	new_node->content = NULL;
	new_node->next = NULL;
	new_node->fd = fd;
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
	if (!(new_node))
		return (NULL);
	ft_lstadd_front(lst, new_node);
	return (new_node);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del && lst->content)
		del(lst->content);
	free(lst);
}

void	ft_lstremove(t_list **lst, t_list *target, t_list *prev)
{
	if (!*lst || !lst || !target)
		return ;
	if (*lst == target)
	{
		*lst = target->next;
		ft_lstdelone(target, free);
	}
	else if (prev)
	{
		prev->next = target->next;
		ft_lstdelone(target, free);
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (!dst && !src)
		return (dst);
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	while (len-- > 0)
		*(tmp_dst++) = *(tmp_src++);
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *) s;
	while (len-- > 0)
		*(tmp_ptr++) = 0;
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	if (!s)
		return (NULL);
	cc = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *) &s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*tmp;
	size_t	i;

	tmp = (char *) malloc((sizeof(char)) * ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (n > len)
		n = len;
	tmp = (char *) malloc(sizeof(char) * (n + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ss = (char *) ft_calloc(len + 1, (sizeof(char)));
	if (!ss)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ss[i] = s[start + i];
		i++;
	}
	return (ss);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	res = (char *) malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (s1)
		ft_memcpy(res, s1, len1);
	if (s2)
		ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}

