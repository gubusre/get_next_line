/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:33:32 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/20 17:36:52 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE = 5

char	*get_next_line (int fd)
{
	void	buffer[BUFFER_SIZE];
	char	*stash;
	size_t	start_line;
	size_t	len_line;
	static size_t	len_fd;
	size_t	i;

	if (!result)
		return (NULL);
	//leer el fichero buffer de tamño X y reiterar?¿
	while (read(fd, buffer , buffer_size - 1) != 0)
	{
		//si en el buffer no se encuentra ningun salto de linea
		ft_strchar((char *)buffer, '\n');
		i = 0;
		while (buffer[i] != '\n')
		{
			//unir la stash con el buffer devuelto
			ft_strjoin(stash, buffer[i]);
			i++;
		//create list, node content == line
		start_line = 0;
		len_fd = 0;
		while (len_fd < size_fd)
		{
			len_line = 0;
			start_line = start_line + len_line;
			while (str[start_line] == '\n')
				start_line++;
			while (str[start_line] != '\n')
				len_line++;
			//crea una string para guardar la linea
			//hacer nuevo nodo
			return (ft_lstnew(ft_substr(str, start, len_line)));
			size_fd = start_line + len_line;
		}
	}
	close(fd);
}
/***************/
int main
{
	int	fd;

	fd = open("/home/gubusque/42/get_next_line/my_txt.txt", O_RDONLY);

}



/*
 * Desc
 * 	line must be finished with \n exept if
 * 	its done with the archive "so check it".
 *
 * Return
 * 	the line have just been read.
 * 	if nothing more to be read return NULL.
 * 	any error return NULL.
 */
