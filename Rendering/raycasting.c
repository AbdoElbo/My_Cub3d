/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:58:13 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/13 18:24:15 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"
// #include "Bonus.h"

// 0 for vertical wall, 1 for horizontal wall
double hit_wall_x(t_dda *dda, t_ray *ray, t_game *game)
{
	if (dda->side == 0)
	{
		dda->raw_dist = dda->side_dist_x - dda->delta_dist_x;
		dda->hit_y = game->player.y + dda->raw_dist * ray->dir_y;
		return (dda->hit_y - floor(dda->hit_y));
	}
	else
	{
		dda->raw_dist = dda->side_dist_y - dda->delta_dist_y;
		dda->hit_x = game->player.x + dda->raw_dist * ray->dir_x;
		return (dda->hit_x - floor(dda->hit_x));
	}
}

//calculate the lenght of the ray to cross exactly one tile in both x and y direction
//if delta_dist_y < delta_dist_x, it means the ray is going going up/down sharper
void init_delta_dist(t_dda *dda, t_ray *ray)
{
	if (ray->dir_x == 0)
		dda->delta_dist_x =  INFINITY;
	else
		dda->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		dda->delta_dist_y =  INFINITY;
	else
		dda->delta_dist_y = fabs(1 / ray->dir_y);
}

void calculate_first_ray_part(t_dda *dda, t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player.x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - game->player.x) * dda->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player.y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - game->player.y) * dda->delta_dist_y;
	}
}

//adding delta_dist to side_dit until wall is hit
void look_for_hit(t_dda *dda, t_game *game)
{
	int hit;
	int tile;

	hit = 0;
	while (!hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		tile = game->map[dda->map_y][dda->map_x];
		if (tile == '1')
		{
			hit = 1;
		}
		else if (tile == 'D' && !check_open_door(dda->map_x, dda->map_y, game))
			hit = 1;
	}
}

static double ft_dda(t_game *game, t_ray *ray)
{
	t_dda	dda;

	dda.map_x = (int)game->player.x;
	dda.map_y = (int)game->player.y;
	init_delta_dist(&dda, ray);
	calculate_first_ray_part(&dda, ray, game);
	look_for_hit(&dda, game);
	ray->side = dda.side;
	ray->wall_x = hit_wall_x(&dda, ray, game);
	ray->distance = dda.raw_dist;
	if (game->map[dda.map_y][dda.map_x] == 'D' && game->texture_door)
		ray->texture_hit = *game->texture_door;
	else if (dda.side == 0 && dda.step_x > 0)
		ray->texture_hit = *game->texture_east;
	else if (dda.side == 0 && dda.step_x < 0)
		ray->texture_hit = *game->texture_west;
	else if (dda.side == 1 && dda.step_y > 0)
		ray->texture_hit = *game->texture_south;
	else if (dda.side == 1 && dda.step_y < 0)
		ray->texture_hit = *game->texture_north;
	return (dda.raw_dist);
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
	distance = ft_dda(game, ray); //seperate into 2 functions, one for measuring distance, one for drawing the line
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
