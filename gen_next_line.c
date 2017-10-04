/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:24:11 by iprokofy          #+#    #+#             */
/*   Updated: 2017/10/03 16:42:56 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_next_line.h"
#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	static char	buffer[BUFF_SIZE];
	static int	start = 0;
	static int	end = 0;
	static int	endln = 0;
	int			pos;
	int			ret;

	if (fd < 0)
		return (-1);
	endln = 0;
	printf("start: %d,end: %d, endln: %d\n", start, end, endln);
	//printf("buffer: %s\n", buffer);
	while ((end < BUFF_SIZE) && endln)
	{
		printf("here1\n");
		if (buffer[end] == '\n' || buffer[end] == EOF)
		{
			printf("start: %d, end: %d\n", start, end);
			endln = 1;
			break;
		}
		end++;
	}
	printf("start: %d,end: %d, endln: %d\n", start, end, endln);
	*line = ft_strsub(buffer, start, end - start);
	printf("start: %d,end: %d, endln: %d\n", start, end, endln);
	end++;
	start = end;
	printf("first part: \"%s\"\n", *line);
	while (!endln)
	{
		printf("here2\n");
		if (!(ret = read(fd, buffer, BUFF_SIZE)))
			return (0);
		printf("\"%s\"\n", buffer);
		printf("%d\n", ret);
		pos = 0;
		while (pos < ret)
		{
			if (buffer[pos] == '\n' || buffer[pos] == EOF)
			{
				printf("here3\n");
				endln = 1;
				char *c2 = ft_strsub(buffer, 0, pos);
				//printf("size: %zu, c2: %s\n", ft_strlen(c2), c2);
				char *tmp = ft_strjoin(*line, c2);
				free(*line);

				//printf("size: %zu, c3: %s\n", ft_strlen(c3), c3);
				*line = tmp;
				printf("line: %s\n", *line);
				//printf("size: %zu, *line: %s\n", ft_strlen(*line), *line);
				start = pos + 1;
				end = start;
				return (0);
			}
			pos++;
			if (pos == ret)
			{
				printf("here4\n");
				char *c2 = ft_strsub(buffer, 0, pos);
				//printf("size: %zu, c2: %s\n", ft_strlen(c2), c2);
				char *c3 = ft_strjoin(*line, c2);
				free(*line);
				*line = c3;
				printf("line: %s\n", *line);
			}
		}
	}
	return (0);
}
