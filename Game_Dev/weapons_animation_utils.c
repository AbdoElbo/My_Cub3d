/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_animation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 15:17:30 by gekko             #+#    #+#             */
/*   Updated: 2026/07/14 16:16:57 by aelbouaz         ###   ########.fr       */
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
	frame_duration = 100;
	now = get_time_in_ms();
	if (now - game->vars.frame_start < frame_duration)
		return ;
	game->vars.frame_start = now;
	if (game->frame == IDLE)
		set_frames(game, img.sword_img_0, img.sword_img_1, ATTACK1);
	else if (game->frame == ATTACK1)
		set_frames(game, img.sword_img_1, img.sword_img_2, ATTACK2);
	else if (game->frame == ATTACK2)
		set_frames(game, img.sword_img_2, img.sword_img_3, ATTACK3);
	else if (game->frame == ATTACK3)
		set_frames(game, img.sword_img_3, img.sword_img_4, ATTACK4);
	else if (game->frame == ATTACK4)
	{
		set_frames(game, img.sword_img_4, img.sword_img_0, IDLE);
		game->movement = FREE;
	}
}

void	shotgun_attack(t_game *game)
{
	long long	now;
	long long	frame_duration;
	t_img		img;

	img = game->images;
	if (game->movement != BUSY)
		return ;
	frame_duration = 100;
	now = get_time_in_ms();
	if (now - game->vars.frame_start < frame_duration)
		return ;
	game->vars.frame_start = now;
	if (game->frame == IDLE)
		set_frames(game, img.shotgun_img_0, img.shotgun_img_1, ATTACK1);
	else if (game->frame == ATTACK1)
		set_frames(game, img.shotgun_img_1, img.shotgun_img_2, ATTACK2);
	else if (game->frame == ATTACK2)
		set_frames(game, img.shotgun_img_2, img.shotgun_img_3, ATTACK3);
	else if (game->frame == ATTACK3)
		set_frames(game, img.shotgun_img_3, img.shotgun_img_4, ATTACK4);
	else if (game->frame == ATTACK4)
	{
		set_frames(game, img.shotgun_img_4, img.shotgun_img_0, IDLE);
		game->movement = FREE;
	}
}
