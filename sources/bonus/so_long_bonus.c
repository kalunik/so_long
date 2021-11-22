/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:56:11 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 03:02:05 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	int		w;
	int		h;
	char	*rule;

	errno = 0;
	rule = ft_strdup("Find keys and go to exit to WIN");
	map_parsing_bonus(argc, argv, &mlx);
	w = mlx.game.width * TILE_SIZE;
	h = mlx.game.height * TILE_SIZE;
	mlx.mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, w, h + 20, "SO LONG");
	main_layer(&mlx);
	mlx_string_put(mlx.mlx, mlx.mlx_win, 5, h + 15, 0xFFFFFF, rule);
	mlx_key_hook(mlx.mlx_win, tap_key_bonus, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0L, red_cross, &mlx);
	mlx_loop_hook(mlx.mlx, animation, &mlx);
	mlx_loop(mlx.mlx);
	if (errno != 0)
		error_n_exit("Unclassified");
	leak_case(mlx.game.height, mlx.game.map);
	free(rule);
	return (0);
}
