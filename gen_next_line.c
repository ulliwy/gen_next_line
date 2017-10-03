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
	static int	endln;
	int			pos;
	int			ret;

	if (fd < 0)
		return (-1);
	endln = 0;
	while ((end < BUFF_SIZE) && endln)
	{
		printf("here1\n");
		if (buffer[end] == '\n' || buffer[end] == EOF)
		{
			printf("start: %d, end: %d\n", start, end);
			endln = 1;
			line = (char **)malloc(sizeof(char) * (end - start + 1));
			*line = ft_strsub(buffer, start, end - start);
			end++;
			start = end;
			break;
		}
		end++;
	}
	pos = 0;
	while (!endln)
	{
		printf("here2\n");
		if (!(ret = read(fd, buffer, BUFF_SIZE)))
			return (0);
		printf("\"%s\"\n", buffer);
		printf("%d\n", ret);
		while (pos < ret)
		{
			if (buffer[pos] == '\n' || buffer[pos] == EOF)
			{
				endln = 1;
				line = (char **)malloc(sizeof(char) * (end - start + pos + 1));
				*line = ft_strjoin(ft_strsub(buffer, start, end - start), ft_strsub(buffer, start, end - start));
				start = pos + 1;
				end = start;
				return (0);
			}
			pos++;
		}
	}
	return (0);
}
