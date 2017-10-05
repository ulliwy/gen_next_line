/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:33:16 by iprokofy          #+#    #+#             */
/*   Updated: 2017/10/05 11:00:23 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

static void simple_string()
{
	char *line;
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;

	fd = 1;
	out = dup(fd);
	pipe(p);
	dup2(p[1], fd);
	write(fd, "aaa", 3);
	close(p[1]);
	dup2(out, fd);
	gnl_ret = get_next_line(p[0], &line);
	assert(strcmp(line, "aaa") == 0);
	assert(gnl_ret == 0 || gnl_ret == 1);
}

int		main (int argc, char **argv)
{
	int		fd1;
	//int		fd2;
	char	*line;

	if (argc != 2)
		return (0);
	fd1 = open(argv[1], O_RDONLY);
	//fd2 = open("test2", O_RDONLY);
	//close(fd);
	printf("result return: %d\n", get_next_line(fd1, &line));
	printf("result line: \"%s\"\n", line);
	printf("-------------------------------\n");
	printf("result return: %d\n", get_next_line(fd1, &line));
	printf("result line: \"%s\"\n", line);
	printf("-------------------------------\n");
	printf("result return: %d\n", get_next_line(fd1, &line));
	printf("result line: \"%s\"\n", line);
	printf("-------------------------------\n");
	printf("result return: %d\n", get_next_line(fd1, &line));
	printf("result line: \"%s\"\n", line);
	printf("-------------------------------\n");
	printf("result return: %d\n", get_next_line(fd1, &line));
	printf("result line: \"%s\"\n", line);
	close(fd1);
	//close(fd2);

	simple_string();
}