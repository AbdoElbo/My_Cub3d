/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:19:18 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/20 14:52:58 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

void	set_animation(t_sprite *sprite, t_anim anim)
{
	if (sprite->current_anim == anim)
		return ;
	if (sprite->current_anim == ANIM_DEATH)
		return ;
	sprite->current_anim = anim;
	sprite->current_frame = 0;
	sprite->frame_timer = 0.0;
	// printf("Animation set successfully!\n");
}

void	destroy_enemy_sprite(t_sprite *sprite, mlx_t *mlx)
{
	int	i;

	if (!sprite)
		return ;
	i = 0;
	while (i < ANIM_COUNT * 13)
	{
		if (sprite->frames && sprite->frames[i])
			mlx_delete_image(mlx, sprite->frames[i]);
		i++;
	}
	free(sprite->frames);
	if (sprite->sheet)
		mlx_delete_texture(sprite->sheet);
}

