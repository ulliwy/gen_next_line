/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:33:16 by iprokofy          #+#    #+#             */
/*   Updated: 2017/10/03 16:32:50 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

int		main (int argc, char **argv)
{
	int		fd;
	char	**line;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	printf("%d\n", get_next_line(fd, line));
	printf("%s\n", *line);
}