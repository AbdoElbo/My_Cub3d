/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:14 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/14 15:51:29 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

void	ft_mouse_mvm(double x, double y, void *param)
{
	t_game	*game;
	int32_t	current_x;
	int32_t	current_y;
	int		dx;
	float	rot_speed;

	(void)y;
	(void)x;
	current_x = 0;
	current_y = 0;
	game = (t_game *)param;
	rot_speed = 0.001f;
	mlx_get_mouse_pos(game->mlx, &current_x, &current_y);
	dx = current_x - game->vars.mouse_x;
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	game->player.angle += dx * rot_speed;
}

void	rotate_player(t_game *game)
{
	float	rot_speed;

	rot_speed = 0.05f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.angle -= rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.angle += rot_speed;
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
