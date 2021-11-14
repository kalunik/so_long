/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_layer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 05:08:03 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/14 05:14:18 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

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

static inline void	one_of_the_buildings(t_mlx *mlx, t_image xpm,
		t_map map_config, int ij[2])
{
	int	random;

	random = (ij[0] + ij[1]) * ij[0] % 4;
	if (random == 0)
		print_xpm_image(mlx, xpm.many_build_alt, ij[0], ij[1]);
	else if (random == 1)
		print_xpm_image(mlx, xpm.build_1_alt, ij[0], ij[1]);
	else if (random == 2)
		print_xpm_image(mlx, xpm.many_build, ij[0], ij[1]);
	else if (random == 3)
		print_xpm_image(mlx, xpm.build_1, ij[0], ij[1]);
}

void	print_xpm_image(t_mlx *mlx, char *img_path, int i, int j)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx->mlx, img_path, &img_w, &img_h);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, j * img_w, i * img_h);
}

static inline void	main_layer_assist(t_mlx *mlx, t_image xpm, int ij[2])
{
	if (ij[0] == 0 && (ij[1] == 0 || ij[1] == mlx->game.width - 1))
		print_xpm_image(mlx, xpm.big_build_3, ij[0], ij[1]);
	else if (ij[0] != (mlx->game.height - 1) && (ij[1] == 0 || ij[1]
			== mlx->game.width - 1))
		print_xpm_image(mlx, xpm.big_build_2, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == 'P')
		print_xpm_image(mlx, xpm.player, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == 'C')
		print_xpm_image(mlx, xpm.collectible, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == 'E')
		print_xpm_image(mlx, xpm.exit, ij[0], ij[1]);
	else if (ij[0] == (mlx->game.height - 1) && (ij[1] == 0 || ij[1]
			== mlx->game.width - 1))
		print_xpm_image(mlx, xpm.big_build_1, ij[0], ij[1]);
	else if (mlx->game.map[ij[0]][ij[1]] == '1')
		one_of_the_buildings(mlx, xpm, mlx->game, ij);
}

void	main_layer(t_mlx *mlx)
{
	int		i;
	int		j;
	int		ij[2];
	t_image	xpm;
	char	**map;

	i = 0;
	j = 0;
	map = mlx->game.map;
	assign_image_path(&xpm);
	mlx->img = xpm;
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
