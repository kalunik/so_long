/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjonatho <wjonatho@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:57:32 by wjonatho          #+#    #+#             */
/*   Updated: 2021/11/22 02:39:23 by wjonatho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "so_long.h"

///utils_bonus
t_location	*create_first_node(int x, int y);
void		add_node_end(int x, int y, t_location *head);
void		clear_ticker(t_mlx *mlx);

///map_bonus
void		*map_parsing_bonus(int argc, char **argv, t_mlx *mlx);

///tap_key_actions_bonus
int			tap_key_bonus(int keycode, t_mlx *mlx);

///animation
int			animation(t_mlx *mlx);

#endif
