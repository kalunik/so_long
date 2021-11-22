/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tap_key_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 05:18:43 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 01:50:57 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	move_player_assist(int key, t_mlx *mlx)
{
	int		*x;
	int		*y;

	x = &mlx->game.player_x;
	y = &mlx->game.player_y;
	print_xpm_image(mlx, mlx->img.blank, *y, *x);
	if (key == KEY_W)
		(*y)--;
	else if (key == KEY_A)
		(*x)--;
	else if (key == KEY_S)
		(*y)++;
	else if (key == KEY_D)
		(*x)++;
	if (mlx->game.end == 1)
		print_xpm_image(mlx, mlx->img.E_3, *y, *x);
	else
		print_xpm_image(mlx, mlx->img.player, *y, *x);
	mlx->game.steps++;
	printf("Steps : %d\n", mlx->game.steps);
}

static inline void	move_player(int key, t_mlx *mlx)
{
	char	next_step;

	next_step = char_ahead(key, mlx);
	if (mlx->game.count_c == 0)
	{
		print_xpm_image(mlx, mlx->img.E_2, mlx->game.exit_y, mlx->game.exit_x);
	}
	if (next_step == '0' || next_step == 'P')
	{
		move_player_assist(key, mlx);
	}
	else if (next_step == 'C')
	{
		move_player_assist(key, mlx);
		mlx->game.count_c--;
		mlx->game.map[mlx->game.player_y][mlx->game.player_x] = '0';
	}
	else if (next_step == 'E' && mlx->game.count_c <= 0)
	{
		mlx->game.end = 1;
		move_player_assist(key, mlx);
	}
}

int	red_cross(void)
{
	exit(EXIT_SUCCESS);
}

int	tap_key(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (mlx->game.end != 0)
		return (EXIT_SUCCESS);
	else if (keycode == KEY_W || keycode == ARROW_UP)
	{
		move_player(KEY_W, mlx);
	}
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
	{
		move_player(KEY_A, mlx);
	}
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
	{
		move_player(KEY_S, mlx);
	}
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
	{
		move_player(KEY_D, mlx);
	}
	return (EXIT_FAILURE);
}
