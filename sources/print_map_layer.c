/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_layer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 05:08:03 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/17 23:16:47 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline void	one_of_the_buildings(t_mlx *mlx, t_image xpm, int ij[2])
{
	int	random;

	random = (ij[0] + ij[1]) * (ij[1] + 2) % 4;
	if (random == 0)
		print_xpm_image(mlx, xpm.many_build_alt, ij[0], ij[1]);
	else if (random == 1)
		print_xpm_image(mlx, xpm.build_1_alt, ij[0], ij[1]);
	else if (random == 2)
		print_xpm_image(mlx, xpm.many_build, ij[0], ij[1]);
	else
		print_xpm_image(mlx, xpm.build_1, ij[0], ij[1]);
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
		one_of_the_buildings(mlx, xpm, ij);
	else if (mlx->game.map[ij[0]][ij[1]] == 'T')
		print_xpm_image(mlx, xpm.thief, ij[0], ij[1]);
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
