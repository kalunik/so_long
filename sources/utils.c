/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 20:51:06 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 01:42:46 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_n_exit(char *err_msg)
{
	printf("Error\n");
	if (errno != 0)
		perror(err_msg);
	else
		printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

void	argv_valid(int argc, char **argv)
{
	if (argc != 2)
		error_n_exit("You should give one argument");
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".ber", 4) != 0)
		error_n_exit("Map for game should have '.ber' extension");
}

void	null_to_map_config(t_mlx *mlx)
{
	mlx->game.map = NULL;
	mlx->game.count_c = 0;
	mlx->game.count_e = 0;
	mlx->game.count_p = 0;
	mlx->game.count_t = 0;
	mlx->game.height = 0;
	mlx->game.width = 0;
	mlx->game.player_x = 0;
	mlx->game.player_y = 0;
	mlx->game.exit_x = 0;
	mlx->game.exit_y = 0;
	mlx->game.steps = 0;
	mlx->game.end = 0;
}

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
	xpm->E_2 = "sprites/exit_2.xpm";
	xpm->E_3 = "sprites/exit_3.xpm";
	xpm->many_build = "sprites/many_buildings_1.xpm";
	xpm->many_build_alt = "sprites/many_buildings_1_alt.xpm";
	xpm->player = "sprites/player.xpm";
	xpm->thief = "sprites/thief.xpm";
}

void	print_xpm_image(t_mlx *mlx, char *img_path, int y, int x)
{
	int		img_w;
	int		img_h;
	void	*img;

	img = mlx_xpm_file_to_image(mlx->mlx, img_path, &img_w, &img_h);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, img, x * img_w, y * img_h);
}
