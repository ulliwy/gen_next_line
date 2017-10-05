/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:24:11 by iprokofy          #+#    #+#             */
/*   Updated: 2017/10/04 17:12:22 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	static char	buffer[BUFF_SIZE];
	char		*nl;
	int			len;

	int			endln;
	int			pos;
	int			ret;
	char		*temp;
	char		*part;
	int			finish;

	if (fd < 0 || !line)
		return (-1);
	finish = 0;
	endln = 0;
	len = ft_strlen(buffer);
	if (len)
	{
		if ((nl = ft_strchr(buffer, '\n')))
		{
			if (b)
		}

	}

	if (is_buff)
	{
		while (end < BUFF_SIZE)
		{
			if (buffer[end] == '\n')
			{
				endln = 1;
				break;
			}
			if (buffer[end] == 0)
				break;
			end++;
		}
	}
	if (is_buff)
		*line = ft_strsub(buffer, start, end - start);
	else
	{
		*line = (char *)malloc(end - start + 1);
		line[0][0] = '\0';
	}
	if (is_buff)
	{
		if (end == BUFF_SIZE)
		{
			end = 0;
			start = 0;
			is_buff = 0;
			ft_bzero(buffer, BUFF_SIZE);
		}
		else
		{
			end++;
			start = end;
		}
	}
	while (!endln && !finish)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		if (ret == -1)
		{
			free(*line);
			return (-1);
		}
		if (ret < BUFF_SIZE)
			finish = 1;
		pos = 0;
		while (pos < ret)
		{
			if (buffer[pos] == '\n')
			{
				endln = 1;
				break;
			}
			pos++;
		}
		part = ft_strsub(buffer, 0, pos);
		temp = (char *)malloc(ft_strlen(*line) + pos + 1);
		temp = ft_strjoin(*line, part);
		free(part);
		free(*line);
		*line = (char *)malloc(ft_strlen(temp) + 1);
		*line = ft_strcpy(*line, temp);
		free(temp);
		if (pos == ret)
		{
			start = 0;
			end = start;
			is_buff = 0;
			ft_bzero(buffer, BUFF_SIZE);
		}
		else
		{
			start = pos + 1;
			end = start;
			is_buff = 1;
		}
	}
	if (!ft_strlen(*line) && buffer[end] == 0 && !endln)
		return (0);
	return (1);
}
