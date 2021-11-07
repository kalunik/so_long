/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:20:28 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/07 16:28:18 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/*int	check_unique(int i, int j, int *count_P, int *count_E)
{
	if (map[i][j] == 'P')
		count_P++;
	if (map[i][j] == 'E')
		count_E++;
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

static inline void	main_layer_assist(t_mlx *mlx, t_image xpm, t_map
					map_config, int ij[2])
{
	if (ij[0] == 0 && (ij[1] == 0 || ij[1] == map_config.width))
		print_xpm_image(mlx, xpm.big_build_3, ij[0], ij[1]);
	else if (ij[0] != (map_config.height - 1) && (ij[1] == 0 || ij[1]
			== map_config.width))
		print_xpm_image(mlx, xpm.big_build_2, ij[0], ij[1]);
	else if (map_config.map[ij[0]][ij[1]] == 'P')
		print_xpm_image(mlx, xpm.player, ij[0], ij[1]);
	else if (map_config.map[ij[0]][ij[1]] == 'C')
		print_xpm_image(mlx, xpm.collectible, ij[0], ij[1]);
	else if (map_config.map[ij[0]][ij[1]] == 'E')
		print_xpm_image(mlx, xpm.exit, ij[0], ij[1]);
	else if (ij[0] == (map_config.height - 1) && (ij[1] == 0 || ij[1]
			== map_config.width))
		print_xpm_image(mlx, xpm.big_build_1, ij[0], ij[1]);
	else if (map_config.map[ij[0]][ij[1]] == '1')
	{
		one_of_the_buildings(mlx, xpm, map_config, ij);
	}
}

void	main_layer(t_mlx *mlx, t_map map_config)
{
	int		i;
	int		j;
	int		ij[2];
	t_data	img;
	t_image	xpm;
	char	**map;

	i = 0;
	j = 0;
	map = map_config.map;
	assign_image_path(&xpm);
	//map_size(map_config);
	while (map[i])
	{
		while (map[i][j])
		{
			ij[0] = i;
			ij[1] = j;
			main_layer_assist(mlx, xpm, map_config, ij);
			printf("%d - %d, %d\n", i, j, map_config.width);
			j++;
			fflush(NULL);
		}
		j = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map_config;
	t_mlx	mlx;

	errno = 0;
	map_parsing(argc, argv, &map_config);
	print_map(map_config.map);
	mlx.mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 13 * SPRITE_SIZE, (5 * SPRITE_SIZE)
			+ 4, "SO LONG");
	main_layer(&mlx, map_config);
	//mlx_string_put(mlx.mlx, mlx.mlx_win, 12, 48, 0xFFFFFF, "HFJ" );
	mlx_loop(mlx.mlx);
	leak_case(map_config.height, map_config.map); //todo нужно помнить кол-во строк
	return (0);
}
