/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:54:10 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/07 14:58:18 by wjonatho         ###   ########.fr       */
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
void	null_to_map_config(t_map *map_config)
{
	map_config->map = NULL;
	map_config->count_C = 0;
	map_config->count_E = 0;
	map_config->count_P = 0;
	map_config->height = 0;
	map_config->width = 0;
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	map_chars_scan(int i, int j, t_map *map_config)
{
	char	**map;

	map = map_config->map;
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' &&
		map[i][j] != 'E' && map[i][j] != 'P')
		return (-1);
	if (map[i][j] == 'C')
		map_config->count_C++;
	if (map[i][j] == 'E')
		map_config->count_E++;
	if (map[i][j] == 'P')
		map_config->count_P++;
	if ((i == 0 || i == map_config->height) && map[i][j] != '1')
		error_n_exit("Map's top or bottom doesn't surrounded by the walls");
	if (i != 0 && (map[i][0] != '1' || map[i][map_config->width] != '1'))
		error_n_exit("Map's L or R sides doesn't surrounded by the walls");
	return (0);
}

void	map_valid(t_map *map_config)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map_config->map[i])
	{
		while (map_config->map[i][j])
		{
			if (map_chars_scan(i, j, map_config))
				error_n_exit("Invalid markup symbols on the map");
			j++;
		}
		j--;
		if (map_config->width == 0)
			map_config->width = j;
		else if (map_config->width != j)
			error_n_exit("Map should be rectangular"); //todo совместить ошибку незакрытой картой
		j = 0;
		i++;
	}
	if (map_config->count_C < 1 || map_config->count_E < 1
		|| map_config->count_P < 1)
		error_n_exit("Some of 'C' or 'E' or 'P' is missing");
}

void	*map_parsing(int argc, char **argv, t_map *map_config)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
	argv_valid(argc, argv);
	null_to_map_config(map_config);
	map_config->height = count_map_lines(argv[1]);
	map_config->map = ft_calloc(map_config->height, sizeof(char **));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_n_exit("Can't read a map");
	while (get_next_line(fd, &buf))
	{
		map_config->map[i++] = ft_strdup(buf);
		free(buf);
	}
	map_valid(map_config);
	return (NULL);
}
