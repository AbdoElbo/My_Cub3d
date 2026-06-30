/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:14 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/30 17:02:56 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

void	rotate_player(t_game *game)
{
	float	rot_speed;

	rot_speed = 0.1f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.angle -= rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.angle += rot_speed;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}
