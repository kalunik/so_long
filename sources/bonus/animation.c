/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 02:48:31 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 02:48:31 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

static inline void	thief_path(t_enemy *image)
{
	image->thief_2 = "sprites/thief_2.xpm";
	image->thief_3 = "sprites/thief_3.xpm";
	image->thief_4 = "sprites/thief_4.xpm";
	image->thief_5 = "sprites/thief_5.xpm";
	image->thief_6 = "sprites/thief_6.xpm";
	image->thief_7 = "sprites/thief_7.xpm";
	image->thief_8 = "sprites/thief_8.xpm";
	image->thief_9 = "sprites/thief_9.xpm";
}

static inline void	animation_assist(char *image_path, t_mlx *mlx)
{
	t_location	*thief;

	thief = mlx->game.thief;
	while (thief)
	{
		print_xpm_image(mlx, image_path, thief->y, thief->x);
		thief = thief->next;
	}
}

int	animation(t_mlx *mlx)
{
	static int	i;
	int			time;

	time = 26;
	thief_path(&(mlx->image));
	if (i < 1 * time)
		animation_assist(mlx->img.thief, mlx);
	else if (i < 2 * time)
		animation_assist(mlx->image.thief_2, mlx);
	else if (i < 3 * time)
		animation_assist(mlx->image.thief_3, mlx);
	else if (i < 4 * time)
		animation_assist(mlx->image.thief_9, mlx);
	else if (i < 5 * time)
		animation_assist(mlx->image.thief_3, mlx);
	else if (i < 6 * time)
		animation_assist(mlx->image.thief_2, mlx);
	else
		i = 0;
	i++;
	return (1);
}
