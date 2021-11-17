/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:20:28 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/17 23:00:22 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	animation(t_mlx *mlx)
{
	static int	i;

	if (i < 100)
		print_xpm_image(mlx, mlx->img.collectible_rev, 1, 11);
	else if (i < 200)
		print_xpm_image(mlx, mlx->img.collectible, 1, 11);
	else
		i = 0;
	i++;
	//mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, mlx->mlx_win);
	return (1);
}

int	animation2(t_mlx *mlx)
{
	int		img_w;
	int		img_h;
	void	*img;
	void	*img1;

	img = mlx_xpm_file_to_image(mlx->mlx, mlx->img.collectible, &img_w, &img_h);
	mlx_sync(1, img);
	mlx_sync(2, mlx->mlx_win);
	img = mlx_xpm_file_to_image(mlx->mlx, mlx->img.collectible_rev, &img_w,
			&img_h);
	mlx_sync(1, img);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, 11 * img_w, 1 * img_h);
	mlx_sync(2, mlx->mlx_win);
	mlx_do_sync(mlx->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	errno = 0;
	map_parsing(argc, argv, &mlx);
	print_map(mlx);
	mlx.mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 13 * TILE_SIZE, (5 * TILE_SIZE)
			+ 5, "SO LONG");
	main_layer(&mlx);
	mlx_key_hook(mlx.mlx_win, tap_key, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0L, red_cross, &mlx);
	mlx_loop_hook(mlx.mlx, animation, &mlx);
	//mlx_loop_hook(mlx.mlx, animation2, &mlx);
	mlx_loop(mlx.mlx);
	if (errno != 0)
		error_n_exit("Unclassified");
	leak_case(mlx.game.height, mlx.game.map);
	return (0);
}
