/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:58:13 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/31 13:12:34 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

void	calculate_first_ray_part(t_dda *dda, t_ray *ray, t_game *g)
{
	if (ray->dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (g->player.x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - g->player.x) * dda->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (g->player.y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - g->player.y) * dda->delta_dist_y;
	}
}

//adding delta_dist to side_dit until wall is hit
void	look_for_hit(t_dda *dda, t_game *game)
{
	int	hit;
	int	tile;

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
		if (tile == '1' || tile == 'e')
			hit = 1;
		else if (tile == 'D' && !check_open_door(dda->map_x, dda->map_y, game))
			hit = 1;
	}
}

static double	ft_dda(t_game *game, t_ray *ray)
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
	if (game->map[dda.map_y][dda.map_x] == 'D' && game->textures.door_tex)
		ray->texture_hit = *game->textures.door_tex;
	else if (game->map[dda.map_y][dda.map_x] == 'e')
		ray->texture_hit = *game->textures.exit_door_tex;
	else if (dda.side == 0 && dda.step_x > 0)
		ray->texture_hit = *game->textures.west_tex;
	else if (dda.side == 0 && dda.step_x < 0)
		ray->texture_hit = *game->textures.east_tex;
	else if (dda.side == 1 && dda.step_y > 0)
		ray->texture_hit = *game->textures.north_tex;
	else if (dda.side == 1 && dda.step_y < 0)
		ray->texture_hit = *game->textures.south_tex;
	return (dda.raw_dist);
}

void	draw_line(t_game *game, t_ray *ray, uint32_t color)
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	distance;

	distance = ft_dda(game, ray);
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
			mlx_put_pixel(game->images.mm_img, x, y, color);
		if (distance <= 0.0)
			break ;
		distance -= 0.01;
	}
}

void	cast_rays(t_game *g)
{
	int		i;
	double	camera_x;

	i = 0;
	while (i < NUM_RAYS)
	{
		camera_x = 2.0 * i / (double)NUM_RAYS - 1.0;
		g->rays[i].angle = g->player.angle;
		g->rays[i].dir_x = g->player.dir_x + g->player.plane_x * camera_x;
		g->rays[i].dir_y = g->player.dir_y + g->player.plane_y * camera_x;
		draw_line(g, &g->rays[i], 0xFF0000FF);
		g->zbuf[i] = g->rays[i].distance;
		i++;
	}
}
