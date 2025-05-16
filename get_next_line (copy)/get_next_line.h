/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:49:32 by gubusque          #+#    #+#             */
/*   Updated: 2025/05/13 16:30:19 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// Define BUFFER_SIZE si no ha sido definido en otro lugar (ej. por flags del compilador)
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// Define el número máximo de descriptores de archivo que tu sistema puede tener abiertos.
// Esto se usa para el array estático de buffers. sysconf(_SC_OPEN_MAX) puede proporcionar
// un valor específico del sistema, pero un valor seguro común como 1024 se usa a menudo para el ejercicio.
#ifndef MAX_FD
# define MAX_FD 1024
#endif

// Inclusiones de librerías estándar
# include <stdlib.h> // Para malloc, free, size_t, NULL
# include <unistd.h> // Para read
# include <limits.h> // Para SIZE_MAX (usado en comprobaciones de desbordamiento)
# include <stdint.h>

// Prototipos de funciones
char    *get_next_line(int fd);
char    *read_file(int fd, char *res); // Auxiliar para leer en buffer
char    *ft_line(char   *buffer);      // Auxiliar para extraer línea
char    *ft_next(char   *buffer);      // Auxiliar para obtener el resto

// Funciones de utilidad (a menudo en un archivo separado)
char    *ft_strjoin(const char *s1, const char *s2);
char    *ft_strchr(const char *s, int c);
char    *ft_free(char *buffer, char *buf);
void    *ft_calloc(size_t count, size_t size);
size_t  ft_strlen(const char *s);
char    *ft_strdup(const char *s1); // Añadida ft_strdup

#endif
