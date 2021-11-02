/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:20:28 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/02 23:38:52 by wjonatho         ###   ########.fr       */
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
	int		i;
	int		fd;
	int		lines_count;
	char	*buf;

	i = 1;
	lines_count = 0;
	fd = open(path_to_map, O_RDONLY);
	if (fd == -1)
		error_n_exit("Can't read a buf");
	while (i > 0)
	{
		i = get_next_line(fd, &buf);
		lines_count += i;
		//printf("i = %d %s\n", i, buf);
		free(buf);
	}
	return (lines_count);
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

/*int	check_unique(int i, int j, int *count_P, int *count_E)
{
	if (map[i][j] == 'P')
		count_P++;
	if (map[i][j] == 'E')
		count_E++;
}*/

int	invalid_map_char(int i, int j, char **map)
{
	if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' &&
					map[i][j] != 'E' && map[i][j] != 'P')
		return (-1);
	return (0);
}

void	map_valid(char **map)
{
	int		i;
	int		j;
	int		count_P;
	int		count_E;

	i = 0;
	j = 0;
	count_P = 0;
	count_E = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (invalid_map_char(i, j, map))
				error_n_exit("Invalid markup symbols on the map");
			if (map[i][j] == 'P')
				count_P++;
			if (map[i][j] == 'E')
				count_E++;
			j++;
		}
		j = 0;
		i++;
	}
	if (count_P > 1 || count_E > 1)
		error_n_exit("To much exit or player");
}

char	**map_parsing(int argc, char **argv, char **map)
{
	int		fd;
	char	*buf;
	int		i;
	int		line_num;

	argv_valid(argc, argv);
	i = 1;
	line_num = 0;
	map = ft_calloc(count_map_lines(argv[1]), sizeof(char **));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_n_exit("Can't read a buf");
	while (i > 0)
	{
		i = get_next_line(fd, &buf);
		if (i > 0)
		{
			map[line_num] = ft_strdup(buf);
			line_num += i;
		}
		free(buf);
	}
	map_valid(map);
	return (map);
}

int	main(int argc, char **argv)
{
	char	**map;
	void	*mlx;
	void	*img;
	void	*mlx_win;

	errno = 0;
	map = NULL;
	map = map_parsing(argc, argv, map);
	print_map(map);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 600, "Hello world!");
	img = mlx_new_image(mlx, 500, 500);
	//mlx_xpm_file_to_image(mlx, "box.XPM", 50, 50);
	mlx_loop(mlx);
	leak_case(5, map); //todo нужно помнить кол-во строк
	return (0);
}
