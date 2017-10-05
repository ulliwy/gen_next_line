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

int		get_buf_param(char *buffer, int *nl)
{
	int		count;
	int 	found;

	count = 0;
	found = 0;
	while (*buffer)
	{
		count++;
		if (!found)
		{
			if (*buffer == '\n')
				found = 1;
			else
				(*nl)++;
		}
		buffer++;
	}
	(*nl)++;
	if (!found)
		*nl = -1;
	return (count);
}

int		get_next_line(const int fd, char **line)
{
	static char	buffer[100][BUFF_SIZE + 1];
	int			nl;
	int			len;
	int			size;
	int			nl2;
	int			found;
	char		*temp;
	char		*part;
	int			ret;

	if (fd < 0 || !line)
		return (-1);

	nl = -1;
	*line = NULL;	
	len = get_buf_param(buffer[fd % 100], &nl);
	//printf("begin buffer: \"%s\"\n", buffer);
	//printf("len: %d, nl: %d\n", len, nl);
	found = 0;
	if (len)
	{
		if (nl != -1)
		{
			*line = ft_strsub(buffer[fd % 100], 0, nl);
			ft_memcpy(buffer[fd % 100], buffer[fd % 100] + nl + 1, len - nl);
			buffer[fd % 100][len - nl - 1] = '\0';
			//printf("buffer22: \"%s\"\n", buffer);
			found = 1;
		}
		else
		{
			*line = ft_strsub(buffer[fd % 100], 0, len);
			//printf("line2: %s\n", *line);
			buffer[fd % 100][0] = '\0';
			//printf("buffer2: \"%s\"\n", buffer);
		}
	}
	nl2 = -1;
	while (!found)
	{
		ret = read(fd, buffer[fd % 100], BUFF_SIZE);
		buffer[fd % 100][ret] = '\0';
		//printf("buffer: %s\n", buffer);
		if (len && ret < BUFF_SIZE)
			found = 1;
		if (!len && !ret)
		{
			//printf("this!!!!!!!\n");
			return (0);
		}
		//printf("ret: %d\n", ret);
		if (ret == -1)
		{	
			return (-1);
		}
		size = get_buf_param(buffer[fd % 100], &nl2);
		//printf("size: %d, nl2: %d\n", size, nl2);
		if (nl2 != -1)
		{
			//printf("here!!!!\n");
			part = ft_strsub(buffer[fd % 100], 0, nl2);
			//printf("part: \"%s\"\n", part);
			//printf("*line: \"%s\"\n", *line);
			if (!(*line))
				*line = part;
			else
			{
				temp = ft_strjoin(*line, part);
				//printf("temp: \"%s\"\n", temp);
				free(*line);
				free(part);
				*line = temp;
			}
			ft_memcpy(buffer[fd % 100], buffer[fd % 100] + nl2 + 1, size - nl2);
			buffer[fd % 100][size - nl2] = '\0';
			//printf("buffer4: %s\n", buffer);
			found = 1;
		}
		else
		{
			//printf("here!\n");
			//printf("*line: %s\n", *line);
			part = ft_strsub(buffer[fd % 100], 0, size);
			//printf("part: %s\n", part);
			if (!(*line))
				*line = part;
			else
			{
				temp = ft_strjoin(*line, part);
				//printf("temp: \"%s\"\n", temp);
				free(*line);
				free(part);
				*line = temp;
			}
			//printf("line3 %s\n", *line);
			buffer[fd % 100][0] = '\0';
			if (size < BUFF_SIZE)
				found = 1;
			//printf("buffer3: \"%s\"\n", buffer);
		}
		//printf("......\n");
	}
	return (1);
}
