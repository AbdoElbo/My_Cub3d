/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:18:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/20 18:04:19 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

mlx_image_t	*get_current_frame(t_sprite *s, int max_frames)
{
	return (s->frames[s->current_anim * max_frames + s->current_frame]);
}

// static void	player_damaged(t_weapons weapon, int *player_hp)
// {
// 	if (weapon == SWORD)
// 	{
// 		*player_hp -= KATANA_DAMAGE;
// 		printf("Player took %d damage\n", KATANA_DAMAGE);
// 	}
// 	else
// 	{
// 		*player_hp -= SHOTGUN_DAMAGE;
// 		printf("Player took %d damage\n", SHOTGUN_DAMAGE);
// 	}
// 	if (*player_hp <= 0)
// 	{
// 		*player_hp = 0;
// 		printf("Player DIED\n");
// 	}
// }

void	update_sprite(t_enemy *enemy, double dt)
{
	t_anim_def	*def;

	enemy->sprite.frame_timer += dt;
	if (enemy->sprite.frame_timer < enemy->sprite.frame_duration)
		return ;
	enemy->sprite.frame_timer = 0.0;
	def = &enemy->sprite.anims[enemy->sprite.current_anim];
	if (enemy->sprite.current_anim == ANIM_HURT
		|| enemy->sprite.current_anim == ANIM_DEATH) // oneshot hurt and death animations
	{
		if (enemy->sprite.current_frame < def->frame_count - 1)
			enemy->sprite.current_frame++;
		if (enemy->sprite.current_anim == ANIM_DEATH && enemy->sprite.current_frame == 8)
			enemy->damage = 0;
		if (enemy->sprite.current_anim == ANIM_HURT && enemy->sprite.current_frame == 4)
			set_animation(&enemy->sprite, ANIM_IDLE);
		return ;
	}
	enemy->sprite.current_frame = (enemy->sprite.current_frame + 1) % def->frame_count;
}

