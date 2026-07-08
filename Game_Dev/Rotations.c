/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:14 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/06 15:31:29 by lpieck           ###   ########.fr       */
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




// 0 for vertical wall, 1 for horizontal wall
static double trace_line_distance(t_game *game, t_ray *ray)
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	raw_dist;
	double	hit_x;
	double	hit_y;

	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	delta_dist_x = (ray->dir_x == 0) ? 1e30 : fabs(1 / ray->dir_x);
	delta_dist_y = (ray->dir_y == 0) ? 1e30 : fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
	}
	hit = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (game->map[map_y][map_x] == '1')
			hit = 1;
	}
	ray->side = side;
	if (side == 0)
	{
		raw_dist = side_dist_x - delta_dist_x;
		hit_y = game->player.y + raw_dist * ray->dir_y;
		ray->wall_x = hit_y - floor(hit_y);
	}
	else
	{
		raw_dist = side_dist_y - delta_dist_y;
		hit_x = game->player.x + raw_dist * ray->dir_x;
		ray->wall_x = hit_x - floor(hit_x);
	}
	ray->distance = raw_dist;
	if (side == 0 && step_x > 0)
		ray->texture_hit = *game->texture_east;
	else if (side == 0 && step_x < 0)
		ray->texture_hit = *game->texture_west;
	else if (side == 1 && step_y > 0)
		ray->texture_hit = *game->texture_south;
	else
		ray->texture_hit = *game->texture_north;
	return (raw_dist);
}

void	draw_line(t_game *game, t_ray *ray, uint32_t color)
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	distance;
	double	step;

	step = 0.01;
	distance = trace_line_distance(game, ray);
	ray->distance = distance;
	i = MINIMAP_PX / 2;
	j = MINIMAP_PX / 2;
	x = i;
	y = j;
	while (distance >= 0.0)
	{
		x = i + ray->dir_x * distance * TILE_SIZE;
		y = j + ray->dir_y * distance * TILE_SIZE;
		if (x > 0 && x < MINIMAP_PX && y > 0 && y < MINIMAP_PX)
			mlx_put_pixel(game->mm_img, x, y, color);
		if (distance <= 0.0)
			break;
		distance -= step;
	}
}

void cast_rays(t_game *game)
{
	int		i;
	double	camera_x;

	i = 0;
	while (i < NUM_RAYS)
	{
		camera_x = 2.0 * i / (double)NUM_RAYS - 1.0;
		game->rays[i].angle = game->player.angle;
		game->rays[i].dir_x = game->player.dir_x + game->player.plane_x * camera_x;
		game->rays[i].dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		draw_line(game, &game->rays[i], 0xFF0000FF);
		i++;
	}
}
