/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:54:10 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/20 21:36:11 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_map_lines(char *path_to_map)
{
	int		fd;
	int		lines_count;
	char	*buf;

	lines_count = 0;
	fd = open(path_to_map, O_RDONLY);
	if (fd == -1)
		error_n_exit("Can't read a buf");
	while (get_next_line(fd, &buf))
	{
		lines_count++;
		free(buf);
	}
	free(buf);
	close(fd);
	return (lines_count);
}

static inline int	map_chars_scan(int i, int j, t_mlx *mlx)
{
	char	**map;

	map = mlx->game.map;
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' &&
		map[i][j] != 'E' && map[i][j] != 'P')
		return (-1);
	if (map[i][j] == 'C')
		mlx->game.count_c++;
	if (map[i][j] == 'E')
		mlx->game.count_e++;
	if (map[i][j] == 'P')
	{
		mlx->game.player_x = j;
		mlx->game.player_y = i;
		mlx->game.count_p++;
	}
	if ((i == 0 || i == mlx->game.height) && map[i][j] != '1')
		error_n_exit("Map's top or bottom doesn't surrounded by the walls");
	if (i != 0 && (map[i][0] != '1' || map[i][mlx->game.width - 1] != '1'))
		error_n_exit("Map's L or R sides doesn't surrounded by the walls");
	return (0);
}

static inline void	map_valid(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mlx->game.height)
	{
		while (j < mlx->game.width)
		{
			if (map_chars_scan(i, j, mlx))
				error_n_exit("Invalid markup symbols on the map");
			j++;
		}
		j = 0;
		i++;
	}
	if (mlx->game.count_c < 1 || mlx->game.count_e < 1
		|| mlx->game.count_p < 1)
		error_n_exit("Some of 'C' or 'E' or 'P' is missing");
}

void	check_map_rectangle(int i, t_mlx *mlx)
{
	if (i == 0)
		mlx->game.width = (int)ft_strlen(mlx->game.map[i++]);
	else if ((int)ft_strlen(mlx->game.map[i++]) != mlx->game.width)
		error_n_exit("Map should be rectangular");
}

void	map_parsing(int argc, char **argv, t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
	argv_valid(argc, argv);
	null_to_map_config(mlx);
	mlx->game.height = count_map_lines(argv[1]);
	mlx->game.map = ft_calloc(mlx->game.height + 1, sizeof(char **));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_n_exit("Can't read a map");
	while (get_next_line(fd, &buf))
	{
		mlx->game.map[i] = ft_strdup(buf);
		check_map_rectangle(i, mlx);
		free(buf);
		i++;
	}
	//mlx->game.map[i] = ft_strdup(buf);
	free(buf);
	close(fd);
	map_valid(mlx);
}
