/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:05:19 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 01:37:27 by wjonatho         ###   ########.fr       */
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
# include "../mlx/mlx.h"

# define TILE_SIZE 48
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define ARROW_UP 126
# define ARROW_LEFT 123
# define ARROW_DOWN 125
# define ARROW_RIGHT 124

typedef struct s_xpm_img_enemy_path {
	char	*thief_2;
	char	*thief_3;
	char	*thief_4;
	char	*thief_5;
	char	*thief_6;
	char	*thief_7;
	char	*thief_8;
	char	*thief_9;
}				t_enemy;

typedef struct s_xpm_image_path {
	char	*big_build_1;
	char	*big_build_2;
	char	*big_build_3;
	char	*blank;
	char	*build_1;
	char	*build_1_alt;
	char	*collectible;
	char	*exit;
	char	*E_2;
	char	*E_3;
	char	*many_build;
	char	*many_build_alt;
	char	*player;
	char	*thief;
}				t_image;

typedef struct s_node{
	struct s_node	*next;
	int				x;
	int				y;
}				t_location;

typedef struct s_map{
	char		**map;
	int			count_c;
	int			count_e;
	int			count_p;
	int			count_t;
	int			height;
	int			width;
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;
	int			steps;
	int			end;
	t_location	*thief;
}				t_map;

typedef struct s_mlx_pointers {
	void	*mlx;
	void	*mlx_win;
	t_map	game;
	t_image	img;
	t_enemy	image;
}				t_mlx;

///map
int		count_map_lines(char *path_to_map);
void	check_map_rectangle(int i, t_mlx *mlx);
void	map_parsing(int argc, char **argv, t_mlx *mlx);

///print_map_layer
void	main_layer(t_mlx *mlx);

///tap_key_actions
char	char_ahead(int key, t_mlx *mlx);
void	move_player_assist(int key, t_mlx *mlx);
int		red_cross(void);
int		tap_key(int keycode, t_mlx *mlx);

///utils
void	error_n_exit(char *err_msg);
void	argv_valid(int argc, char **argv);
void	null_to_map_config(t_mlx *mlx);
void	assign_image_path(t_image *xpm);
void	print_xpm_image(t_mlx *mlx, char *img_path, int y, int x);

#endif
