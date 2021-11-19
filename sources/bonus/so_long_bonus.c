/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:56:11 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/20 00:52:53 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	clear_ticker(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < mlx->game.width)
	{
		print_xpm_image(mlx, mlx->img.blank, mlx->game.height, x);
		x++;
	}
}

static inline int	map_chars_scan_bonus(int i, int j, t_mlx *mlx)
{
	char	**map;

	map = mlx->game.map;
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' &&
		map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != 'T')
		return (-1);
	if (map[i][j] == 'C')
		mlx->game.count_c++;
	if (map[i][j] == 'E')
		mlx->game.count_e++;
	if (map[i][j] == 'P')
	{
		mlx->game.player_x = j;
		mlx->game.player_y = i;
		mlx->game.count_p++;
	}
	if ((i == 0 || i == mlx->game.height) && map[i][j] != '1')
		error_n_exit("Map's top or bottom doesn't surrounded by the walls");
	if (i != 0 && (map[i][0] != '1' || map[i][mlx->game.width - 1] != '1'))
		error_n_exit("Map's L or R sides doesn't surrounded by the walls");
	return (0);
}

static inline void	map_valid_bonus(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mlx->game.height)
	{
		while (j < mlx->game.width)
		{
			if (map_chars_scan_bonus(i, j, mlx))
				error_n_exit("Invalid markup symbols on the map");
			j++;
		}
		j = 0;
		i++;
	}
	if (mlx->game.count_c < 1 || mlx->game.count_e < 1
		|| mlx->game.count_p < 1)
		error_n_exit("Some of 'C' or 'E' or 'P' is missing");
}

void	*map_parsing_bonus(int argc, char **argv, t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
	argv_valid(argc, argv);
	null_to_map_config(mlx);
	mlx->game.height = count_map_lines(argv[1]);
	mlx->game.map = ft_calloc(mlx->game.height + 1, sizeof(char **));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_n_exit("Can't read a map");
	while (get_next_line(fd, &buf))
	{
		mlx->game.map[i] = ft_strdup(buf);
		check_map_rectangle(i, mlx);
		free(buf);
		i++;
	}
	free(buf);
	close(fd);
	map_valid_bonus(mlx);
	return (NULL);
}

void	exit_coordinates(t_mlx *mlx, int *x, int *y)
{
	while (mlx->game.map[*y])
	{
		while (mlx->game.map[*y][*x])
		{
			if (mlx->game.map[*y][*x] == 'E')
				break ;
			(*x)++;
		}
		*x = 0;
		(*y)++;
	}
}

static inline void	move_player_bonus(int key, t_mlx *mlx)
{
	char	next_step;
	int		y;
	char	*str_step;
	int	i;
	int	j;

	clear_ticker(mlx);
	y = (mlx->game.height * TILE_SIZE) + 15;
	str_step = ft_itoa(mlx->game.steps);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, y, 0xFFFFFF, str_step);
	free(str_step);
	next_step = char_ahead(key, mlx);
	if (next_step == '0' || next_step == 'P')
	{
		move_player_assist(key, mlx);
	}
	else if (next_step == 'T')
	{
		move_player_assist(key, mlx);
		mlx->game.end = 1;
		print_xpm_image(mlx, mlx->img.thief, mlx->game.player_y, mlx->game.player_x);
		clear_ticker(mlx);
		mlx_string_put(mlx->mlx, mlx->mlx_win, 5, y, 0xFFFFFF, "FAIL! Avoid enemies");
	}
	else if (next_step == 'C')
	{
		move_player_assist(key, mlx);
		mlx->game.count_c--;
		mlx->game.map[mlx->game.player_y][mlx->game.player_x] = '0';
	}
	else if (next_step == 'E' && mlx->game.count_c <= 0)
	{
		move_player_assist(key, mlx);
		mlx->game.end = 1;
		clear_ticker(mlx);
		mlx_string_put(mlx->mlx, mlx->mlx_win, 5, y, 0xFFFFFF, "YOU WIN!");
	}
	if (mlx->game.count_c == 0)
	{


		i = 0;
		j = 0;
		exit_coordinates(mlx, &i, &j);
		printf("%d -- %d\n", i, j);
	}

}

int	tap_key_bonus(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (mlx->game.end != 0)
		return (EXIT_SUCCESS);
	else if (keycode == KEY_W || keycode == ARROW_UP)
	{
		move_player_bonus(KEY_W, mlx);
	}
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
	{
		move_player_bonus(KEY_A, mlx);
	}
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
	{
		move_player_bonus(KEY_S, mlx);
	}
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
	{
		move_player_bonus(KEY_D, mlx);
	}
	return (EXIT_FAILURE);
}

void	thief_path(t_enemy *thief)
{
	thief->thief_2 = "sprites/xpm/thief_2.xpm";
	thief->thief_3 = "sprites/xpm/thief_3.xpm";
	thief->thief_4 = "sprites/xpm/thief_4.xpm";
	thief->thief_5 = "sprites/xpm/thief_5.xpm";
	thief->thief_6 = "sprites/xpm/thief_6.xpm";
	thief->thief_7 = "sprites/xpm/thief_7.xpm";
	thief->thief_8 = "sprites/xpm/thief_8.xpm";
	thief->thief_9 = "sprites/xpm/thief_9.xpm";
}

int	animation(t_mlx *mlx)
{
	static int	i;

	thief_path(&(mlx->thief));
	if (i < 10)
		print_xpm_image(mlx, mlx->img.thief, 1, 2);
	else if (i < 20)
		print_xpm_image(mlx, mlx->thief.thief_2, 1, 2);
	else if (i < 30)
		print_xpm_image(mlx, mlx->thief.thief_3, 1, 2);
	else if (i < 40)
		print_xpm_image(mlx, mlx->thief.thief_9, 1, 2);
	else if (i < 50)
		print_xpm_image(mlx, mlx->thief.thief_3, 1, 2);
	else if (i < 60)
		print_xpm_image(mlx, mlx->thief.thief_2, 1, 2);
	else
		i = 0;
	i++;
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	errno = 0;
	map_parsing_bonus(argc, argv, &mlx); //'T' добавлен, думаю характеристики не важны
	mlx.mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.game.width * TILE_SIZE, (mlx.game
				.height * TILE_SIZE) + 20, "SO LONG");
	main_layer(&mlx);
	mlx_string_put(mlx.mlx, mlx.mlx_win, 5, (5 * TILE_SIZE) + 15, 0xFFFFFF,
				   "Find keys and go to exit to WIN");
	mlx_key_hook(mlx.mlx_win, tap_key_bonus, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0L, red_cross, &mlx);
	mlx_loop_hook(mlx.mlx, animation, &mlx);
	mlx_loop(mlx.mlx);
	if (errno != 0)
		error_n_exit("Unclassified");
	leak_case(mlx.game.height, mlx.game.map);
	return (0);
}