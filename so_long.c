/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:20:28 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/13 17:04:28 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/*int	check_unique(int i, int j, int *count_p, int *count_e)
{
	if (map[i][j] == 'P')
		count_p++;
	if (map[i][j] == 'E')
		count_e++;
}*/

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

/*int	map_size(t_map map_config)
{

}*/

void	assign_image_path(t_image *xpm)
{
	xpm->big_build_1 = "sprites/big_building_1.xpm";
	xpm->big_build_2 = "sprites/big_building_2.xpm";
	xpm->big_build_3 = "sprites/big_building_3.xpm";
	xpm->blank = "sprites/blank.xpm";
	xpm->build_1 = "sprites/building_1.xpm";
	xpm->build_1_alt = "sprites/building_1_alt.xpm";
	xpm->collectible = "sprites/collectible.xpm";
	xpm->exit = "sprites/exit.xpm";
	xpm->many_build = "sprites/many_buildings_1.xpm";
	xpm->many_build_alt = "sprites/many_buildings_1_alt.xpm";
	xpm->player = "sprites/player.xpm";
	xpm->thief = "sprites/thief.xpm";
}

void	print_xpm_image(t_mlx *mlx, char *img_path, int i, int j)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx->mlx, img_path, &img_w, &img_h);
	//printf("w h %d %d\n", img_w, img_h);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, j * img_w, i * img_h);
}

void	one_of_the_buildings(t_mlx *mlx, t_image xpm, t_map map_config,
							 int ij[2])
{
	int	random;

	random = (ij[0] + ij[1]) % 4;
	if (random == 0)
		print_xpm_image(mlx, xpm.many_build_alt, ij[0], ij[1]);
	else if (random == 1)
		print_xpm_image(mlx, xpm.build_1_alt, ij[0], ij[1]);
	else if (random == 2)
		print_xpm_image(mlx, xpm.many_build, ij[0], ij[1]);
	else if (random == 3)
		print_xpm_image(mlx, xpm.build_1, ij[0], ij[1]);
}

static inline void	main_layer_assist(t_mlx *mlx, t_image xpm, int ij[2])
{
	if (ij[0] == 0 && (ij[1] == 0 || ij[1] == mlx->game.width))
		print_xpm_image(mlx, xpm.big_build_3, ij[0], ij[1]);
	else if (ij[0] != (mlx->game.height - 1) && (ij[1] == 0 || ij[1]
			== mlx->game.width))
		print_xpm_image(mlx, xpm.big_build_2, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == 'P')
		print_xpm_image(mlx, xpm.player, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == 'C')
		print_xpm_image(mlx, xpm.collectible, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == 'E')
		print_xpm_image(mlx, xpm.exit, ij[0], ij[1]);
	else if (ij[0] == (mlx->game.height - 1) && (ij[1] == 0 || ij[1]
			== mlx->game.width))
		print_xpm_image(mlx, xpm.big_build_1, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == '1')
	{
		one_of_the_buildings(mlx, xpm, mlx->game, ij);
	}
}

/*int	no_wall_ahead(int x, int y, t_mlx *mlx)
{
	if (mlx->game.map[y][x] != 1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}*/

char	char_ahead(int key, t_mlx *mlx)
{
	int	x;
	int	y;

	x = mlx->game.player_x;
	y = mlx->game.player_y;
	if (key == KEY_W)
		return (mlx->game.map[y - 1][x]);
	else if (key == KEY_A)
		return (mlx->game.map[y][x - 1]);
	else if (key == KEY_S)
		return (mlx->game.map[y + 1][x]);
	else if (key == KEY_D)
		return (mlx->game.map[y][x + 1]);
	return (EXIT_FAILURE);
}

void	move_player(int key, t_mlx *mlx)
{
	int		*x;
	int		*y;
	char	next_step;

	x = &mlx->game.player_x;
	y = &mlx->game.player_y;
	next_step = char_ahead(key, mlx);
	if (next_step == '0' || next_step == 'P')
	{
		print_xpm_image(mlx, mlx->img.blank, *y, *x);
		if (key == KEY_W)
			(*y)--;
		else if (key == KEY_A)
			(*x)--;
		else if (key == KEY_S)
			(*y)++;
		else if (key == KEY_D)
			(*x)++;
		print_xpm_image(mlx, mlx->img.player, *y, *x);
		mlx->game.steps++;
		printf("Steps : %d\n", mlx->game.steps);
	}
	else if (next_step == 'C')
	{
		mlx->game.count_c--;
		print_xpm_image(mlx, mlx->img.blank, *y, *x);
		if (key == KEY_W)
			(*y)--;
		else if (key == KEY_A)
			(*x)--;
		else if (key == KEY_S)
			(*y)++;
		else if (key == KEY_D)
			(*x)++;
		mlx->game.map[*y][*x] = '0';
		print_xpm_image(mlx, mlx->img.player, *y, *x);
		mlx->game.steps++;
		printf("Steps : %d\n", mlx->game.steps);
	}
	else if (next_step == 'E' && mlx->game.count_c == 0)
	{
		mlx->game.count_c--;
		print_xpm_image(mlx, mlx->img.blank, *y, *x);
		if (key == KEY_W)
			(*y)--;
		else if (key == KEY_A)
			(*x)--;
		else if (key == KEY_S)
			(*y)++;
		else if (key == KEY_D)
			(*x)++;
		print_xpm_image(mlx, mlx->img.player, *y, *x);
		mlx->game.steps++;
		printf("Steps : %d\n", mlx->game.steps);
		mlx->game.end = 1;
	}
}

int	red_cross(int keycode, t_mlx *mlx)
{
	exit(EXIT_SUCCESS);
}

int	actions(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (mlx->game.end != 0)
		return (EXIT_SUCCESS);
	else if (keycode == KEY_W)
	{
		move_player(KEY_W, mlx);
	}
	else if (keycode == KEY_A)
	{
		move_player(KEY_A, mlx);
	}
	else if (keycode == KEY_S)
	{
		move_player(KEY_S, mlx);
	}
	else if (keycode == KEY_D)
	{
		move_player(KEY_D, mlx);
	}
	return (EXIT_FAILURE);
}

int	tap_key(int keycode, t_mlx *mlx)
{
	actions(keycode, mlx);
	return (0);
}

void	main_layer(t_mlx *mlx)
{
	int		i;
	int		j;
	int		ij[2];
	t_data	img;
	t_image	xpm;
	char	**map;

	i = 0;
	j = 0;
	map = mlx->game.map;
	assign_image_path(&xpm);
	mlx->img = xpm;
	//map_size(map_config);
	while (map[i])
	{
		while (map[i][j])
		{
			ij[0] = i;
			ij[1] = j;
			main_layer_assist(mlx, xpm, ij);
			j++;
		}
		j = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	errno = 0;
	map_parsing(argc, argv, &mlx); //fixme вылетала сега, по идее исправлена
	print_map(mlx);
	mlx.mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 13 * SPRITE_SIZE, (5 * SPRITE_SIZE)
			+ 20, "SO LONG");
	main_layer(&mlx);
	mlx_key_hook(mlx.mlx_win, tap_key, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0L, red_cross, &mlx);
	//printf("Steps: %d\n", mlx.game.steps);
	print_xpm_image(&mlx, mlx.img.blank, 0, (4 * SPRITE_SIZE) + 15);
	mlx_string_put(mlx.mlx, mlx.mlx_win, 0, (5 * SPRITE_SIZE) + 15,
		0xFFFFFF, ft_itoa(mlx.game.steps));
	mlx_loop(mlx.mlx);
	if (errno != 0)
		error_n_exit("Unclassified");
	leak_case(mlx.game.height, mlx.game.map); //todo нужно помнить кол-во строк
	return (0);
}
