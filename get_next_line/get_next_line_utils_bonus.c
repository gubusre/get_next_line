/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gubusque <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/19 16:39:34 by gubusque		  #+#	#+#			 */
/*   Updated: 2025/05/19 17:22:42 by gubusque         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h> 

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;
	size_t	total_len;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (len1 > SIZE_MAX - len2 - 1)
		return (NULL);
	total_len = len1 + len2;
	res = ft_calloc(total_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i] != '\0')
		{
			res[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
	{
		while (s2[j] != '\0')
		{
			res[i + j] = s2[j];
			j++;
		}
	}
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

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

char	*ft_free(char *buffer, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, buf);
	if (!tmp)
		return (NULL);
	free(buffer);
	return (tmp);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	unsigned char	*start;
	size_t			total_size;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total_size = count * size;
	tmp = malloc(total_size);
	if (!tmp)
		return (NULL);
	start = tmp;
	while (total_size-- > 0)
		*(tmp++) = 0;
	return (start);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	return (res);
}
