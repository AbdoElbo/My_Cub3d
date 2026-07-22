/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:54:00 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/17 15:20:32 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

//render_angle = angle ponting from player to enemy
//angle_diff = difference between dir of player and angle to enemy
//how smaller, how closer to center
static double	get_angle_diff(t_game *game, t_enemy *enemy)
{
	double	render_angle;
	double	angle_diff;

	render_angle = atan2(enemy->y - game->player.y, enemy->x - game->player.x);
	angle_diff = render_angle - game->player.angle;
	enemy->aim_angle = angle_diff;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	return (angle_diff);
}

static int	enemy_visible(t_enemy *enemy, double angle_diff, double *depth)
{
	if (angle_diff < -FOV / 2 || angle_diff > FOV /2)
		return (0);
	if (enemy->dst_from_player <= 0.1)
		return (0);
	*depth = enemy->dst_from_player * cos(angle_diff);
	if (*depth <= 0.1)
		return (0);
	return (1);
}

static t_projection	compute_projection(double angle_diff, double depth)
{
	t_projection	projection;

	projection.depth = depth;
	projection.screen_x = (int)((SCREEN_WIDTH / 2.0) * (1.0 + tan(angle_diff) / tan(FOV / 2.0))); // ??
	projection.size = (int)(SCREEN_HEIGHT / depth);
	projection.start_x = projection.screen_x - projection.size / 2;
	projection.start_y = SCREEN_HEIGHT / 2 - projection.size / 2 - projection.size / 4; // ??
	return (projection);
}

static void	draw_enemy_column(t_game *game, mlx_image_t *frame,
	t_projection *projection, int x)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	if (projection->depth >= game->zbuf[x])
		return ;
	if (projection->start_y < 0)
		y = 0;
	else
		y = projection->start_y;
	tex_x = (x - projection->start_x) * frame->width / projection->size;
	while (y < projection->start_y + projection->size && y < SCREEN_HEIGHT)
	{
		tex_y = (y - projection->start_y) * frame->height / projection->size;
		color = ((uint32_t *)frame->pixels)[tex_y * frame->width + tex_x];
		if (color & 0xFF)
			((uint32_t *)game->framebuf->pixels)[y * game->framebuf->width + x] = color;
		y++;
	}

}

static void draw_enemy_sprite(t_game *game, mlx_image_t *frame, t_projection *projection)
{
	int	x;

	if (projection->start_x < 0)
		x = 0;
	else
		x = projection->start_x;
	while (x < projection->start_x + projection->size && x < SCREEN_WIDTH)
	{
		draw_enemy_column(game, frame, projection, x);
		x++;
	}
}

void	render_enemy(t_game *game, t_enemy *enemy)
{
	double			depth;
	double			angle_diff;
	mlx_image_t		*frame;
	t_projection	projection ;

	angle_diff = get_angle_diff(game, enemy);
	if (!enemy_visible(enemy, angle_diff, &depth))
		return ;
	update_sprite(enemy, game->mlx->delta_time);
	frame = get_current_frame(&enemy->sprite, 13);
	projection = compute_projection(angle_diff, depth);
	draw_enemy_sprite(game, frame, &projection);
}
