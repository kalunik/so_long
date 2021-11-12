/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:54:10 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/12 21:17:12 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

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
	size_t	len;

	if (argc != 2)
	{
		error_n_exit("You should give one argument");
	}
	len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1] + (len - 4), ".ber", 4) != 0)
		error_n_exit("Map for game should have .ber extension");
}

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
	return (lines_count);
}
void	null_to_map_config(t_mlx *mlx)
{
	mlx->game.map = NULL;
	mlx->game.count_c = 0;
	mlx->game.count_e = 0;
	mlx->game.count_p = 0;
	mlx->game.height = 0;
	mlx->game.width = 0;
	mlx->game.player_x = 0;
	mlx->game.player_y = 0;
}

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

int	map_chars_scan(int i, int j, t_mlx *mlx)
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

void	map_valid(t_mlx *mlx)
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
/*		j--;
		if (mlx->game.width == 0)
			mlx->game.width = j;
		else if (mlx->game.width != j)
			error_n_exit("Map should be rectangular"); //todo совместить ошибку незакрытой картой*/
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
		mlx->game.width = ft_strlen(mlx->game.map[i++]);
	else if (ft_strlen(mlx->game.map[i++]) != mlx->game.width)
		error_n_exit("Map should be rectangular");
}

void	*map_parsing(int argc, char **argv, t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*buf;
	int		len;

	i = 0;
	argv_valid(argc, argv);
	null_to_map_config(mlx);
	mlx->game.height = count_map_lines(argv[1]);
	mlx->game.map = ft_calloc(mlx->game.height, sizeof(char **));
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
	//print_map(mlx->game.map);
	map_valid(mlx);
	return (NULL);
}
