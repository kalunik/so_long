/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:05:19 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/09 11:21:22 by wjonatho         ###   ########.fr       */
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

# define SPRITE_SIZE 100
typedef struct s_map{
	char	**map;
	int		count_C;
	int		count_E;
	int		count_P;
	int		height;
	int		width;
}				t_map;

typedef struct s_xpm_image_path {
	char	*big_build_1;
	char	*big_build_2;
	char	*big_build_3;
	char	*build_1;
	char	*build_1_alt;
	char	*collectible;
	char	*exit;
	char	*many_build;
	char	*many_build_alt;
	char	*player;
	char	*thief;
}				t_image;

typedef struct s_mlx_pointers {
	void	*mlx;
	void	*mlx_win;
}				t_mlx;

void	error_n_exit(char *err_msg);
void	*map_parsing(int argc, char **argv, t_map *map_config);
void	print_map(char **map);
void	assign_image_path(t_image *xpm);

#endif
