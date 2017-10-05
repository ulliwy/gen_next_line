/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:24:11 by iprokofy          #+#    #+#             */
/*   Updated: 2017/10/05 11:50:45 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_buf_param(char *buffer, int *nl)
{
	int		count;
	int		found;

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

void	get_line(char **line, int len, char buffer[FDN][BUFF_SIZE + 1], int fd)
{
	char	*part;
	char	*temp;

	part = ft_strsub(buffer[fd % FDN], 0, len);
	if (!(*line))
		*line = part;
	else
	{
		temp = ft_strjoin(*line, part);
		free(*line);
		free(part);
		*line = temp;
	}
}

int		get_from_buff(char (*buffer)[FDN][BUFF_SIZE + 1], int fd, int *len,
	char **line)
{
	int		found;
	int		nl;

	nl = -1;
	found = 0;
	*len = get_buf_param((*buffer)[fd % FDN], &nl);
	if (*len)
	{
		if (nl != -1)
		{
			*line = ft_strsub((*buffer)[fd % FDN], 0, nl);
			ft_memcpy((*buffer)[fd % FDN], (*buffer)[fd % FDN] + nl + 1,
				*len - nl);
			(*buffer)[fd % FDN][*len - nl - 1] = '\0';
			found = 1;
		}
		else
		{
			*line = ft_strsub((*buffer)[fd % FDN], 0, *len);
			(*buffer)[fd % FDN][0] = '\0';
		}
	}
	return (found);
}

int		get_from_file(char (*buffer)[FDN][BUFF_SIZE + 1], int fd, char **line)
{
	int		size;
	int		nl;
	int		found;

	found = 0;
	nl = -1;
	size = get_buf_param((*buffer)[fd % FDN], &nl);
	if (nl != -1)
	{
		get_line(line, nl, (*buffer), fd);
		ft_memcpy((*buffer)[fd % FDN], (*buffer)[fd % FDN] + nl + 1, size - nl);
		(*buffer)[fd % FDN][size - nl] = '\0';
		found = 1;
	}
	else
	{
		get_line(line, size, (*buffer), fd);
		(*buffer)[fd % FDN][0] = '\0';
		if (size < BUFF_SIZE)
			found = 1;
	}
	return (found);
}

int		get_next_line(const int fd, char **line)
{
	static char	buffer[FDN][BUFF_SIZE + 1];
	int			len;
	int			found;
	int			ret;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	found = get_from_buff(&buffer, fd, &len, line);
	while (!found)
	{
		ret = read(fd, buffer[fd % FDN], BUFF_SIZE);
		buffer[fd % FDN][ret] = '\0';
		if (len && ret < BUFF_SIZE)
			found = 1;
		if (!len && !ret)
			return (0);
		if (ret == -1)
			return (-1);
		found = get_from_file(&buffer, fd, line);
	}
	return (1);
}
