/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:05:19 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/04 14:19:33 by wjonatho         ###   ########.fr       */
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
	char	**map;
	int		count_C;
	int		count_E;
	int		count_P;
	int		height;
	int		width;
}				t_map;

void	error_n_exit(char *err_msg);
void	*map_parsing(int argc, char **argv, t_map *map_config);
void	print_map(char **map);

#endif
