/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/24 21:49:32 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/05/19 19:15:48 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*read_file(int fd, char *res);
char	*ft_line(char *buffer);
char	*ft_next(char *buffer);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_free(char *buffer, char *buf);
char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

#endif
