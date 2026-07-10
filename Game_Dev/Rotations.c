/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:14 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/09 10:59:06 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

void	rotate_player(t_game *game)
{
	float	rot_speed;

	rot_speed = 0.05f;
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
    game->player.plane_x = -game->player.dir_y * tan(FOV / 2.0);
    game->player.plane_y = game->player.dir_x * tan(FOV / 2.0);
}

// static double	trace_line_distance(t_game *game, t_ray *ray, double step)
// {
// 	double	distance;
// 	double	world_x;
// 	double	world_y;

// 	distance = 0.0;
// 	while (distance < game->width || distance < game->height)
// 	{
// 		world_x = game->player.x + ray->dir_x * distance;
// 		world_y = game->player.y + ray->dir_y * distance;
// 		if (hits_wall(game, world_x, world_y))
// 			break;
// 		distance += step;
// 	}
// 	return (distance);
// }





