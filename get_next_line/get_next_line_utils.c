/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:47:53 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/22 18:21:49 by gubusque         ###   ########.fr       */
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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstremove(t_list **lst, t_list *node, t_list *prev)
{
	if (!lst || !node)
		return ;
	if (!prev)
		return ;
	else
		prev->next = node->next;
	ft_lstdelone(node, free);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == (void *)0 && src == (void *)0)
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
	size_t			i;

	i = 0;
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
	while (str[len++])
	{
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

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	i;

	dst = (char *) malloc(ft_strlen(s1) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_strndup(const char *s1, size_t len)
{
	char	*dst;
	size_t	i;

	dst = (char *) malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i] && len > 0)
	{
		dst[i] = s1[i];
		i++;
		len--;
	}
	dst[i] = 0;
	return (dst);
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

