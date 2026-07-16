/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:18:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/16 15:23:54 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static mlx_image_t	*get_current_frame(t_sprite *s, int max_frames)
{
	return (s->frames[s->current_anim * max_frames + s->current_frame]);
}

static void	update_sprite(t_enemy *enemy, double dt)
{
	t_anim_def	*def;

	enemy->sprite.frame_timer += dt;
	if (enemy->sprite.frame_timer < enemy->sprite.frame_duration)
		return ;
	enemy->sprite.frame_timer = 0.0;
	def = &enemy->sprite.anims[enemy->sprite.current_anim];
	if (enemy->sprite.current_anim == ANIM_HURT || enemy->sprite.current_anim == ANIM_DEATH) // oneshot hurt and death animations
	{
		if (enemy->sprite.current_frame < def->frame_count - 1)
			enemy->sprite.current_frame++;
		if (enemy->sprite.current_anim == ANIM_DEATH && enemy->sprite.current_frame == 8)
			enemy->damage = 0;
		return ;
	}
	enemy->sprite.current_frame = (enemy->sprite.current_frame + 1) % def->frame_count;
}

void	test_sprite_loop(t_game *game, t_enemy *enemy)
{
	mlx_image_t	*frame;
	uint32_t	*src;
	uint32_t	*dst;
	uint32_t	y;
	uint32_t	x;

	if (!game->enemy || game->vars.enemy_count <= 0)
		return ;
	update_sprite(enemy, game->mlx->delta_time);
	frame = get_current_frame(&enemy->sprite, 13);
	src = (uint32_t *)frame->pixels;
	dst = (uint32_t *)game->framebuf->pixels;
	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			if (src[y * frame->width + x] & 0xFF)
				dst[y * game->framebuf->width + x] = src[y * frame->width + x];
			x++;
		}
		y++;
	}
}
