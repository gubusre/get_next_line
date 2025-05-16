/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:54:52 by gubusque          #+#    #+#             */
/*   Updated: 2025/05/13 17:00:54 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h> // Asegurarse de incluir stdint.h aquí también para SIZE_MAX si es necesario

/*
 * Reads data from the file descriptor and appends it to the result buffer
 * until a newline is encountered in the accumulated buffer or EOF is reached.
 * Returns the accumulated buffer or NULL on read error or if the file was empty.
 */
char    *read_file(int fd, char *res)
{
    char    *buffer;
    int     byte_read;
    char    *temp_res;

    // Allocate temporary buffer for reading
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buffer) // Check allocation of buffer
    {
        // If buffer allocation fails, and res was already allocated, free res.
        // If res was NULL, nothing to free.
        if (res)
             free(res); // Free the accumulated buffer if it exists
        return (NULL); // Return NULL on buffer allocation failure
    }

    // Loop while we can read bytes AND the accumulated result 'res' does NOT contain a newline
    // The condition `!ft_strchr(res, '\n')` is only checked if res is not NULL.
    while (1) // Loop indefinitely, break conditions inside
    {
        // If res contains a newline, we have a full line. Break the read loop.
        // Check res is not NULL before calling ft_strchr
        if (res && ft_strchr(res, '\n'))
            break;

        byte_read = read(fd, buffer, BUFFER_SIZE);

        if (byte_read == -1)
        {
            free(buffer); // Free the temporary buffer
            if (res) // Free res if it was allocated before the error
                 free(res); // Free the accumulated buffer
            return (NULL); // Return NULL on read error
        }

        // If byte_read is 0, it's EOF. Break the loop.
        if (byte_read == 0)
            break; // Break on EOF

        buffer[byte_read] = '\0'; // Null-terminate the data read into the temporary buffer

        // If res is NULL, this is the first read with data. Allocate memory for res and copy buffer.
        if (!res)
        {
            res = ft_strdup(buffer); // ft_strdup allocates and copies
            if (!res) // Check allocation failure
            {
                free(buffer);
                return (NULL); // Return NULL on res allocation failure
            }
        }
        else // If res is already allocated, append the new data
        {
            temp_res = ft_free(res, buffer); // ft_free joins and frees the old 'res'
            if (!temp_res) // Check allocation failure during ft_free/ft_strjoin
            {
                free(buffer);
                // Original 'res' was NOT freed by ft_free if ft_strjoin failed.
                // The original 'res' is still valid here.
                free(res); // FREE the original res buffer here if ft_free failed
                return (NULL); // Return NULL on join/reallocation failure
            }
            res = temp_res; // Update res to the new buffer
        }
    }

    free(buffer); // Free the temporary read buffer

    // If we reached EOF (byte_read was 0) and res is still NULL,
    // it means the file was empty.
    if (byte_read == 0 && !res)
        return (NULL);

    return (res); // Return the accumulated buffer (or NULL from error)
}

/*
 * Extracts the first line from the buffer (up to and including the newline).
 * Returns the extracted line or NULL on allocation failure or if buffer is NULL or empty.
 */
char    *ft_line(char   *buffer)
{
    char    *line;
    int     i;
    int     len;

    // If the buffer is NULL or empty, there is no line to extract
    if (!buffer || buffer[0] == '\0')
        return (NULL);

    i = 0;
    // Find the position of the first newline or the end of the string
    while (buffer[i] && buffer[i] != '\n')
        i++;

    // Calculate the length of the line to extract.
    // It's i characters + 1 if there's a newline + 1 for the null terminator.
    len = i + 1; // Length up to and including the character at buffer[i]
    if (buffer[i] == '\n') // If buffer[i] is '\n', we need space for it
        len++; // Add space for the null terminator

    line = ft_calloc(len, sizeof(char)); // Allocate memory for the line

    // Check for allocation failure
    if (!line)
        return (NULL);

    i = 0;
    // Copy the characters of the line
    while (buffer[i] && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }

    // If a newline was found, copy it
    if (buffer[i] == '\n')
    {
        line[i] = '\n';
        i++;
    }

    line[i] = '\0'; // Null-terminate the extracted line

    return (line); // Returns NEWLY allocated line
}

/*
 * Extracts the remainder of the buffer after the first newline character.
 * Frees the original buffer.
 * Returns the new remainder buffer or NULL if no remainder exists.
 */
char    *ft_next(char   *buffer)
{
    char    *remainder;
    int     i;
    int     j;
    size_t  len;

    i = 0;
    // Find the position of the first newline or the end of the string
    while (buffer[i] && buffer[i] != '\n')
        i++;

    // If no newline is found, this is the last line. There is no remainder.
    if (!buffer[i])
    {
        free(buffer); // Free the buffer containing the last line
        return (NULL); // No remainder
    }

    // Newline found at buffer[i]
    len = ft_strlen(buffer);
    // Size needed is for characters AFTER the newline + null terminator
    // Number of chars after newline is len - (i + 1)
    // Size = (len - (i + 1)) + 1 = len - i
    // If the newline is the last character, i = len - 1.
    // Size = len - (len - 1) = 1. This is correct for the null terminator.
    remainder = ft_calloc((len - i), sizeof(char)); // Allocate memory size (len - i)

    if (!remainder) // Check for allocation failure
    {
        free(buffer); // Free the original buffer on failure
        return (NULL);
    }

    i++; // Move past the newline
    j = 0;
    // Copy characters from buffer[i] onwards to remainder[j]
    while (buffer[i]) // Loop until the null terminator of the original buffer
        remainder[j++] = buffer[i++];

    remainder[j] = '\0'; // Null-terminate the remainder

    free(buffer); // Free the original buffer
    return (remainder); // Returns NEWLY allocated remainder
}


/*
 * Reads a line from a file descriptor.
 * Uses a static buffer array to store leftover data between calls for each FD.
 * Returns the next line read from the file, or NULL if EOF is reached or an error occurs.
 */
char    *get_next_line(int fd)
{
    static char *buffer[MAX_FD]; // Static array for buffers per FD
    char        *line;

    // Basic error checks for file descriptor and BUFFER_SIZE.
    // Relying on read_file to handle invalid FDs and read errors.
    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
    {
        // If there's an existing buffer for this FD on error, free it.
        if (fd >= 0 && fd < MAX_FD && buffer[fd]) // Added bounds check for fd
        {
            free(buffer[fd]);
            buffer[fd] = NULL; // Explicitly set to NULL
        }
        return (NULL);
    }

    // Read data into the buffer for this FD. read_file stops at newline in res or EOF.
    // read_file handles invalid FDs and read errors by returning NULL.
    buffer[fd] = read_file(fd, buffer[fd]);

    // If buffer[fd] is NULL after reading, it means read_file failed or the file was empty/EOF.
    if (!buffer[fd])
    {
        // If read_file returned NULL, the buffer for this FD is now NULL (either was NULL
        // initially or was freed by read_file on error/empty file).
        // Nothing more to free here for this FD's buffer.
        return (NULL); // Return NULL if read_file failed or EOF
    }

    // Extract the line from the buffer. ft_line allocates new memory.
    line = ft_line(buffer[fd]);

    // If line is NULL, it means ft_line failed (likely malloc) or the buffer
    // contained no characters to form a line (which shouldn't happen if buffer[fd] is not NULL).
    if (!line)
    {
        // Malloc failure during line extraction. Free the accumulated buffer for this FD.
        free(buffer[fd]);
        buffer[fd] = NULL; // Set to NULL after freeing
        return (NULL);
    }

    // Update the buffer to contain only the remainder after the extracted line.
    // ft_next frees the old buffer and returns the new remainder.
    buffer[fd] = ft_next(buffer[fd]);
    // Note: ft_next returns NULL if there is no remainder (last line).
    // This is handled correctly; buffer[fd] becomes NULL.

    return (line); // Return the extracted line
}