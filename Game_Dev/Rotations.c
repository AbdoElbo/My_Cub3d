/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:14 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/02 18:30:57 by aelbouaz         ###   ########.fr       */
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
	// next 4 lines are kinda unnnecessary
	// but it's good to give the angle a range of 0 -> PI * 2
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle >= 2 * PI)
		game->player.angle -= 2 * PI;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

void	draw_line(t_game *game, uint32_t color)
{
	int		i;
	int		j;
	double	x = 0.00001f;
	double	y = 0.00001f;
	double	distance;

	distance = 0;
	i = MINIMAP_PX / 2;
	j = MINIMAP_PX / 2;
	while (distance < MINIMAP_PX)
	{
		x = i + game->player.dir_x * distance;
		y = j + game->player.dir_y * distance;
		if (x > 0 && x < MINIMAP_PX && y > 0 && y < MINIMAP_PX)
			mlx_put_pixel(game->mm_img, x, y, color);
		distance++;
	}
}
