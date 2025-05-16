/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:28:15 by gubusque          #+#    #+#             */
/*   Updated: 2025/05/13 17:00:29 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * Joins two strings into a new string.
 * Handles NULL input strings.
 * Returns the new joined string or NULL on allocation failure or overflow.
 * Uses ft_calloc to ensure memory is zero-initialized, potentially
 * resolving Valgrind uninitialized value warnings.
 */
char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *res;
    size_t  len1;
    size_t  len2;
    size_t  i;
    size_t  j;
    size_t  total_len;

    len1 = 0;
    len2 = 0;
    if (s1)
        len1 = ft_strlen(s1);
    if (s2)
        len2 = ft_strlen(s2);

    // Added overflow check for total length + 1 for null terminator
    if (len1 > SIZE_MAX - len2 - 1)
        return (NULL);

    total_len = len1 + len2;

    // Allocate memory for the combined length + null terminator using ft_calloc
    res = ft_calloc(total_len + 1, sizeof(char)); // Use ft_calloc here
    if (!res)
        return (NULL);

    i = 0;
    // Copy s1 if it exists
    if (s1)
    {
        while (s1[i] != '\0')
        {
            res[i] = s1[i];
            i++;
        }
    }

    j = 0;
    // Copy s2 if it exists, starting after s1
    if (s2)
    {
        while (s2[j] != '\0')
        {
            res[i + j] = s2[j];
            j++;
        }
        // Null-terminate the result after copying s2 (redundant with ft_calloc but harmless)
        // res[i + j] = '\0';
    }
    // else
    // {
        // If s2 was NULL, just null-terminate after s1 (redundant with ft_calloc but harmless)
        // res[i] = '\0';
    // }
    return (res);
}

/*
 * Locates the first occurrence of character c in string s.
 * Returns a pointer to the located character, or NULL if not found.
 * Handles the null terminator character ('\0').
 */
char    *ft_strchr(const char *s, int c)
{
    unsigned int    i;
    char            cc;

    cc = (char) c;
    i = 0;
    // Iterate through the string
    while (s[i] != '\0')
    {
        if (s[i] == cc)
            return ((char *) &s[i]); // Retorna puntero al carácter
        i++;
    }
    // Check if the character searched was the null terminator
    if (cc == '\0')
        return ((char *) &s[i]); // Retorna puntero al terminador nulo
    return (NULL); // Carácter no encontrado
}

/*
 * Helper function used in read_file to append 'buf' to 'buffer' and free 'buffer'.
 * Returns the new combined string or NULL on allocation failure.
 * Corrected to free the old buffer ONLY if ft_strjoin succeeds.
 */
char    *ft_free(char *buffer, char *buf)
{
    char    *tmp;

    // Join the current buffer with the new data read into buf
    tmp = ft_strjoin(buffer, buf);
    if (!tmp) // Check allocation BEFORE freeing the old buffer
    {
        // If ft_strjoin failed, the original buffer is still valid.
        // We should NOT free the original buffer here if ft_strjoin failed.
        return (NULL); // Indicate failure
    }
    free(buffer); // Free the old buffer ONLY if ft_strjoin succeeded
    return (tmp);
}

/*
 * Allocates memory for an array of 'count' elements, each of 'size' bytes,
 * and sets all bytes in the allocated memory to zero.
 * Returns a pointer to the allocated memory, or NULL on allocation failure or overflow.
 * Corrected to return the start of the allocated memory.
 */
void    *ft_calloc(size_t count, size_t size)
{
    unsigned char   *tmp;
    unsigned char   *start; // Pointer to store the start of allocated memory
    size_t  total_size;

    // Added overflow check
    if (size != 0 && count > SIZE_MAX / size)
        return (NULL);

    total_size = count * size;
    tmp = malloc(total_size);
    if (!tmp)
        return (NULL);

    start = tmp; // Store the original starting address

    // Zero out the allocated memory
    while (total_size-- > 0)
        *(tmp++) = 0;

    // Return the original starting address
    return (start); // CORREGIDO: Retornando el puntero 'start' original
}

/*
 * Calculates the length of a string.
 * Returns the number of characters in the string, excluding the null terminator.
 * Returns 0 if the input string is NULL.
 */
size_t  ft_strlen(const char *s)
{
    size_t  len;

    len = 0;
    if (!s) // Handle NULL input string
        return (0);
    while (s[len]) // Count characters until the null terminator
        len++;
    return (len);
}

/*
 * Duplicates a string.
 * Returns a pointer to the newly allocated duplicated string, or NULL on allocation failure.
 * Uses ft_calloc to ensure zero-initialization.
 */
char *ft_strdup(const char *s1)
{
    char *res;
    size_t len;
    size_t i;

    len = ft_strlen(s1);
    res = ft_calloc(len + 1, sizeof(char)); // Use ft_calloc here
    if (!res)
        return (NULL);
    i = 0;
    while (i < len)
    {
        res[i] = s1[i];
        i++;
    }
    // res[i] = '\0'; // Redundant with ft_calloc but harmless
    return (res);
}