/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tap_key_actions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 02:38:49 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 03:18:48 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static inline void	thief_logics(int y, int key, t_mlx *mlx)
{
	int		p_x;
	int		p_y;
	char	*fail;

	move_player_assist(key, mlx);
	p_x = mlx->game.player_x;
	p_y = mlx->game.player_y;
	fail = ft_strdup("FAIL! Avoid enemies");
	mlx->game.end = 2;
	print_xpm_image(mlx, mlx->img.thief, p_y, p_x);
	clear_ticker(mlx);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, y, 0xFFFFFF, fail);
	free(fail);
}

static inline void	exit_logics(int y, int key, t_mlx *mlx)
{
	mlx->game.end = 1;
	move_player_assist(key, mlx);
	clear_ticker(mlx);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, y, 0xFFFFFF, "YOU WIN!");
}

static inline void	steps_on_ticker(int y, t_mlx *mlx)
{
	char	*str_step;

	clear_ticker(mlx);
	str_step = ft_itoa(mlx->game.steps);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 5, y, 0xFFFFFF, str_step);
	free(str_step);
}

static inline void	move_player_bonus(int key, t_mlx *mlx)
{
	char	next_step;
	int		y;

	y = (mlx->game.height * TILE_SIZE) + 15;
	next_step = char_ahead(key, mlx);
	if (mlx->game.count_c == 0)
		print_xpm_image(mlx, mlx->img.E_2, mlx->game.exit_y, mlx->game.exit_x);
	if (next_step == '0' || next_step == 'P')
		move_player_assist(key, mlx);
	else if (next_step == 'T')
		thief_logics(y, key, mlx);
	else if (next_step == 'C')
	{
		move_player_assist(key, mlx);
		mlx->game.count_c--;
		mlx->game.map[mlx->game.player_y][mlx->game.player_x] = '0';
	}
	else if (next_step == 'E' && mlx->game.count_c <= 0)
		exit_logics(y, key, mlx);
	if (mlx->game.end == 0)
		steps_on_ticker(y, mlx);
}

int	tap_key_bonus(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (mlx->game.end != 0)
		return (EXIT_SUCCESS);
	else if (keycode == KEY_W || keycode == ARROW_UP)
		move_player_bonus(KEY_W, mlx);
	else if (keycode == KEY_A || keycode == ARROW_LEFT)
		move_player_bonus(KEY_A, mlx);
	else if (keycode == KEY_S || keycode == ARROW_DOWN)
		move_player_bonus(KEY_S, mlx);
	else if (keycode == KEY_D || keycode == ARROW_RIGHT)
		move_player_bonus(KEY_D, mlx);
	return (EXIT_FAILURE);
}
