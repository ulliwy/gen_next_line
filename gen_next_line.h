/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iprokofy <iprokofy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:24:22 by iprokofy          #+#    #+#             */
/*   Updated: 2017/10/03 16:28:09 by iprokofy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_NEXT_LINE_H
# define GEN_NEXT_LINE_H

# include <stdlib.h>
# include "libft/libft.h"

# define BUFF_SIZE 10
# define EOF (-1)

int		get_next_line(const int fd, char **line);

#endif
