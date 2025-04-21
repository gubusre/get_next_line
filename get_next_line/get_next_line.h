/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:31:34 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/15 19:54:36 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

typedef struct s_list
{
	char	*line;
	s_list	*next;

} t_list

char	*get_next_line(int fd);
t_list	*ft_lstnew(char *line);	
unsigned int	ft_check(void *to_check, void *checker);
