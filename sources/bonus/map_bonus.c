/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 02:23:47 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 02:28:45 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static inline void	map_parsing_assist(int argc, char **argv, t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
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
	free(buf);
	close(fd);
}

static inline int	map_chars_scan_bonus(int i, int j, t_mlx *mlx)
{
	char		**map;

	map = mlx->game.map;
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' &&
		map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != 'T')
		return (-1);
	if (map[i][j] == 'C')
		mlx->game.count_c++;
	if (map[i][j] == 'E')
	{
		mlx->game.exit_x = j;
		mlx->game.exit_y = i;
		mlx->game.count_e++;
	}
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

static inline void	map_valid_bonus(t_mlx *mlx)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mlx->game.height)
	{
		while (j < mlx->game.width)
		{
			if (map_chars_scan_bonus(i, j, mlx))
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

static inline void	find_enemy(t_location	**enemy, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (mlx->game.map[y])
	{
		while (mlx->game.map[y][x])
		{
			if (mlx->game.map[y][x] == 'T')
			{
				if (mlx->game.count_t == 0)
					*enemy = create_first_node(x, y);
				else
					add_node_end(x, y, *enemy);
				mlx->game.count_t++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	*map_parsing_bonus(int argc, char **argv, t_mlx *mlx)
{
	t_location	*enemy;

	argv_valid(argc, argv);
	null_to_map_config(mlx);
	map_parsing_assist(argc, argv, mlx);
	map_valid_bonus(mlx);
	find_enemy(&enemy, mlx);
	mlx->game.thief = enemy;
	return (NULL);
}
