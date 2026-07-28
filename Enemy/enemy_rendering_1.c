/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_rendering_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 14:54:00 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/28 13:26:35 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static void	draw_sprite_column(t_game *game, mlx_image_t *frame,
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
		{
			((uint32_t *)game->framebuf->pixels)
			[y * game->framebuf->width + x] = color;
		}
		y++;
	}
}

void	draw_sprite(t_game *game, mlx_image_t *frame, t_projection *projection)
{
	int	x;

	if (projection->start_x < 0)
		x = 0;
	else
		x = projection->start_x;
	while (x < projection->start_x + projection->size && x < SCREEN_WIDTH)
	{
		draw_sprite_column(game, frame, projection, x);
		x++;
	}
}

static int	enemy_behind_wall(t_game *game, t_enemy *enemy)
{
	double	step_x;
	double	step_y;
	double	x;
	double	y;
	double	steps;

	steps = enemy->dst_from_player / 0.01;
	step_x = (enemy->x - game->player.x) / steps;
	step_y = (enemy->y - game->player.y) / steps;
	x = game->player.x;
	y = game->player.y;
	while (steps-- > 0)
	{
		x += step_x;
		y += step_y;
		if (game->map[(int)y][(int)x] == '1'
			|| (game->map[(int)y][(int)x] == 'D'
			&& !door_is_open(game, (int)x, (int)y)))
		{
			enemy->visible = false;
			return (1);
		}
	}
	enemy->visible = true;
	return (0);
}

void	render_enemy(t_game *game, t_enemy *enemy)
{
	double			depth;
	double			angle_diff;
	mlx_image_t		*frame;
	t_projection	projection ;

	angle_diff = get_angle_diff(game, enemy);
	if (!sprite_visible(enemy, angle_diff, &depth))
		return ;
	update_sprite(enemy, game->mlx->delta_time);
	frame = get_current_frame(&enemy->sprite, 13);
	projection = compute_projection(angle_diff, depth, 2.0f, 0.65f);
	draw_sprite(game, frame, &projection);
	enemy_behind_wall(game, enemy);
}
