/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 02:31:51 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 02:31:51 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

t_location	*create_first_node(int x, int y)
{
	t_location	*node;

	node = malloc(sizeof(t_location));
	if (node == NULL)
		exit(0);
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

void	add_node_end(int x, int y, t_location *head)
{
	t_location	*node;
	t_location	*tmp;

	node = malloc(sizeof(t_location));
	if (node == NULL)
		exit(0);
	node->x = x;
	node->y = y;
	node->next = NULL;
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	clear_ticker(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < mlx->game.width)
	{
		print_xpm_image(mlx, mlx->img.blank, mlx->game.height, x);
		x++;
	}
}
