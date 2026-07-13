/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_animation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 15:17:30 by gekko             #+#    #+#             */
/*   Updated: 2026/07/13 16:42:18 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static void	set_frames(t_game *game, mlx_image_t *img1
		, mlx_image_t *img2, t_frame next)
{
	img1->enabled = false;
	img2->enabled = true;
	game->frame = next;
}

void	sword_attack(t_game *game)
{
	long long	now;
	long long	frame_duration;
	t_img		img;

	img = game->images;
	if (game->movement != BUSY)
		return ;
	frame_duration = 50;
	now = get_time_in_ms();
	if (now - game->frame_start < frame_duration)
		return ;
	game->frame_start = now;
	if (game->frame == IDLE)
		set_frames(game, img.sword_img_0, img.sword_img_1, ATTACK1);
	else if (game->frame == ATTACK1)
		set_frames(game, img.sword_img_1, img.sword_img_2, ATTACK2);
	else if (game->frame == ATTACK2)
		set_frames(game, img.sword_img_2, img.sword_img_3, ATTACK3);
	else if (game->frame == ATTACK3)
	{
		set_frames(game, img.sword_img_3, img.sword_img_0, IDLE);
		game->movement = FREE;
	}
}

void	other_attack(t_game *game)
{
	long long	now;
	long long	frame_duration;
	t_img		img;

	img = game->images;
	if (game->movement != BUSY)
		return ;
	frame_duration = 100;
	now = get_time_in_ms();
	if (now - game->frame_start < frame_duration)
		return ;
	game->frame_start = now;
	if (game->frame == IDLE)
		set_frames(game, img.other_img_0, img.other_img_1, ATTACK1);
	else if (game->frame == ATTACK1)
		set_frames(game, img.other_img_1, img.other_img_2, ATTACK2);
	else if (game->frame == ATTACK2)
		set_frames(game, img.other_img_2, img.other_img_3, ATTACK3);
	else if (game->frame == ATTACK3)
	{
		set_frames(game, img.other_img_3, img.other_img_0, IDLE);
		game->movement = FREE;
	}
}
