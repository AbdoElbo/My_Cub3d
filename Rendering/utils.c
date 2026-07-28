/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:45:28 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 15:21:23 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

void	order_enemy_array(t_enemy *enemies, int enemy_count)
{
	t_enemy	temp;
	int		i;
	int		j;

	i = 0;
	while (i < enemy_count)
	{
		j = i + 1;
		while (j < enemy_count)
		{
			if (enemies[j].dst_from_player > enemies[i].dst_from_player)
			{
				temp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = temp;
			}
			j++;
		}
		i++;
	}
}

// 0 for vertical wall, 1 for horizontal wall
double	hit_wall_x(t_dda *dda, t_ray *ray, t_game *game)
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

//calculate the lenght of the ray to cross exactly one
// tile in both x and y direction if delta_dist_y < delta_dist_x,
// it means the ray is going going up/down sharper
void	init_delta_dist(t_dda *dda, t_ray *ray)
{
	if (ray->dir_x == 0)
		dda->delta_dist_x = INFINITY;
	else
		dda->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		dda->delta_dist_y = INFINITY;
	else
		dda->delta_dist_y = fabs(1 / ray->dir_y);
}
