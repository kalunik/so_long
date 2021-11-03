/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:20:28 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/03 23:18:46 by wjonatho         ###   ########.fr       */
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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(int argc, char **argv)
{
	t_map	map_config;
	t_data	img;
	void	*mlx;
	void	*mlx_win;
	int		img_width;
	int		img_height;

	errno = 0;
	map_parsing(argc, argv, &map_config);
	print_map(map_config.map);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 120, 120, "Hello world!");
	img.img = mlx_xpm_file_to_image(mlx, "box.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	//mlx_string_put(mlx, mlx_win, 1, 60, 25500, "HFJ" );
	mlx_loop(mlx);
	leak_case(map_config.height, map_config.map); //todo нужно помнить кол-во строк
	return (0);
}
