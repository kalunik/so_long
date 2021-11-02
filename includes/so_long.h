/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:05:19 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/02 19:07:15 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <sys/fcntl.h>
# include <sys/errno.h>
# include <unistd.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"

typedef struct s_map{
	int		count_P;
	int		count_E;
}				t_map_check;

#endif
