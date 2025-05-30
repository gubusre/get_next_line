/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:26:49 by gubusque          #+#    #+#             */
/*   Updated: 2025/04/23 18:39:20 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

int main() {
	int fd1 = open("file1.txt", O_RDONLY);
	int fd2 = open("file2.txt", O_RDONLY);
	int fd3 = open("file3.txt", O_RDONLY);
	char *line;

	printf("--- Reading from fd1 ---\n");
	while ((line = get_next_line(fd1)))
	{
		printf("FD1: %s", line);
		free(line);
	}
	printf("\n--- Reading from fd2 ---\n");
	while ((line = get_next_line(fd2)) != NULL)
	{
		printf("FD2: %s", line);
		free(line);
	}
	printf("\n--- Reading from fd3 ---\n");
        while ((line = get_next_line(fd3)) != NULL)
	{
		printf("FD2: %s", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
}
