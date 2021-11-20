/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:20:28 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/19 21:08:21 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_mlx mlx)
{
	int	i;

	i = 0;
	while (mlx.game.map[i])
	{
		printf("%s\n", mlx.game.map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	errno = 0;
	map_parsing(argc, argv, &mlx);
	print_map(mlx);
	mlx.mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.game.width * TILE_SIZE,
			(mlx.game.height * TILE_SIZE) + 5, "SO LONG");
	main_layer(&mlx);
	mlx_key_hook(mlx.mlx_win, tap_key, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0L, red_cross, &mlx);
	mlx_loop(mlx.mlx);
	if (errno != 0)
		error_n_exit("Unclassified");
	leak_case(mlx.game.height, mlx.game.map);
	return (0);
}
