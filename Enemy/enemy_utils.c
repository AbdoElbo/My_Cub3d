/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:19:18 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 13:10:51 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

void	delete_blood(t_game *game)
{
	long long	now;
	long long	frame_duration;

	frame_duration = 500;
	now = get_time_in_ms();
	if (now - game->vars.last_hit < frame_duration)
		return ;
	game->images.getting_hurt->enabled = false;
	game->vars.last_hit = 0;
}

void	set_animation(t_sprite *sprite, t_anim anim)
{
	if (sprite->current_anim == anim)
		return ;
	if (sprite->current_anim == ANIM_DEATH)
		return ;
	sprite->current_anim = anim;
	sprite->current_frame = 0;
	sprite->frame_timer = 0.0;
}

void	destroy_enemy_sprite(t_sprite *sprite)
{
	if (!sprite)
		return ;
	free(sprite->frames);
	if (sprite->sheet)
		mlx_delete_texture(sprite->sheet);
}
