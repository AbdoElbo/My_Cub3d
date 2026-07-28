/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rendering_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 13:20:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 13:30:30 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

//render_angle = angle ponting from player to enemy
//angle_diff = difference between dir of player and angle to enemy
//how smaller, how closer to center
double	get_angle_diff(t_game *game, t_enemy *enemy)
{
	double	render_angle;
	double	angle_diff;

	render_angle = atan2(enemy->y - game->player.y, enemy->x - game->player.x);
	angle_diff = render_angle - game->player.angle;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	enemy->aim_angle = angle_diff;
	return (angle_diff);
}

int	sprite_visible(t_enemy *enemy, double angle_diff, double *depth)
{
	if (angle_diff < -FOV / 2 || angle_diff > FOV / 2)
		return (0);
	*depth = enemy->dst_from_player * cos(angle_diff);
	if (*depth <= 0.1)
		return (0);
	return (1);
}

t_projection	compute_projection(double angle_diff, double depth,
					float size, float height)
{
	t_projection	projection;

	projection.depth = depth;
	projection.screen_x = (int)((SCREEN_WIDTH / 2.0)
			* (1.0 + tan(angle_diff) / tan(FOV / 2.0)));
	projection.size = (int)((SCREEN_HEIGHT / depth) * size);
	projection.start_x = projection.screen_x - projection.size / 2;
	projection.start_y = SCREEN_HEIGHT / 2 - height * projection.size;
	return (projection);
}
