/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:31:34 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/23 22:25:45 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_list
{
	char		*content;
	int		fd;
	struct s_list	*next;
} t_list;

char	*get_next_line(int fd);
t_list	*ft_lstnew(int	fd);
t_list  *ft_lstfind(t_list **lst, int fd);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strndup(const char *s1, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	ft_lstremove(t_list **lst, t_list *node, t_list *prev);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);

#endif
