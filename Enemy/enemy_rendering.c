// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   enemy_rendering.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/07/17 14:54:00 by lpieck            #+#    #+#             */
// /*   Updated: 2026/07/17 15:20:32 by lpieck           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "enemy.h"

void	render_enemy(t_game *game, t_enemy *enemy)
{
	mlx_image_t	*frame;
	double		depth;
	double		render_angle;
	double		angle_diff;
	int			screen_x;
	int			size;
	int			start_x;
	int			start_y;
	int			x;
	int			y;

	render_angle = atan2(enemy->y - game->player.y, enemy->x - game->player.x);
	angle_diff = render_angle - game->player.angle;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	if (angle_diff < -FOV / 2 || angle_diff > FOV / 2)
		return ;
	if (enemy->dst_from_player <= 0.1)
		return ;
	depth = enemy->dst_from_player * cos(angle_diff);
	if (depth <= 0.1)
		return ;
	update_sprite(enemy, game->mlx->delta_time);
	frame = get_current_frame(&enemy->sprite, 13);
	screen_x = (int)((0.5 + angle_diff / FOV) * SCREEN_WIDTH);
	size = (SCREEN_HEIGHT / depth);
	start_x = screen_x - size / 2;
	start_y = SCREEN_HEIGHT / 2 - size / 2 - 50;
	x = (start_x < 0) ? 0 : start_x;
	while (x < start_x + size && x < SCREEN_WIDTH)
	{
		if (depth < game->zbuf[x]) // occluded by a nearer wall? skip column
		{
			y = (start_y < 0) ? 0 : start_y;
			while (y < start_y + size && y < SCREEN_HEIGHT)
			{
				uint32_t	color;
				int			tex_x;
				int			tex_y;

				tex_x = (x - start_x) * frame->width / size;
				tex_y = (y - start_y) * frame->height / size;
				color = ((uint32_t *)frame->pixels)[tex_y * frame->width + tex_x];
				if (color & 0xFF)
					((uint32_t *)game->framebuf->pixels)[y * game->framebuf->width + x] = color;
				y++;
			}
		}
		x++;
	}
}