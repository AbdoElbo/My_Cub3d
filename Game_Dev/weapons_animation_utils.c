/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_animation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 15:17:30 by gekko             #+#    #+#             */
/*   Updated: 2026/07/28 13:47:50 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static void	get_multiplier(int *damage, float distance)
{
	if (distance > 4 && distance < 5)
		*damage *= 0.4;
	else if (distance > 3 && distance < 4)
		*damage *= 0.6;
	else if (distance > 2 && distance < 3)
		*damage *= 0.8;
	else if (distance > 1 && distance < 2)
		*damage *= 1;
}

static void	damage_enemies(t_game *game, double distance
		, int damage, float field)
{
	int	i;

	i = 0;
	while (i < game->vars.enemy_count)
	{
		if (damage == SHOTGUN_DAMAGE)
			get_multiplier(&damage, game->enemy[i].dst_from_player);
		if (game->enemy[i].aim_angle < field && game->enemy[i].health
			&& game->enemy[i].aim_angle > -field && game->enemy[i].visible
			&& game->enemy[i].dst_from_player < distance)
		{
			if (game->enemy[i].health - damage <= 0)
			{
				game->enemy[i].health = 0;
				set_animation(&game->enemy[i].sprite, ANIM_DEATH);
				printf("ENEMY %d DIED\n", i);
			}
			else
			{
				game->enemy[i].health -= damage;
				printf("ENEMY %d TOOK %d DAMAGE (has %d hp)\n", i,
					damage, game->enemy[i].health);
				set_animation(&game->enemy[i].sprite, ANIM_HURT);
			}
		}
		i++;
	}
}

static void	set_frames(t_game *game, mlx_image_t *img1
		, mlx_image_t *img2, t_frame next)
{
	img1->enabled = false;
	img2->enabled = true;
	game->frame = next;
	if (next == IDLE)
		game->movement = FREE;
	if (next == ATTACK2)
	{
		if (game->weapon == SWORD)
			damage_enemies(game, 1, KATANA_DAMAGE, KATANA_FIELD);
		else
			damage_enemies(game, 3.5f, SHOTGUN_DAMAGE, SHOTGUN_FIELD);
	}
}

void	sword_attack(t_game *game)
{
	long long	now;
	long long	frame_duration;
	t_img		img;

	img = game->images;
	if (game->movement != BUSY)
		return ;
	frame_duration = 70;
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
		set_frames(game, img.sword_img_4, img.sword_img_0, IDLE);
}

void	shotgun_attack(t_game *game)
{
	long long	now;
	long long	frame_duration;
	t_img		img;

	img = game->images;
	if (game->movement != BUSY)
		return ;
	frame_duration = 80;
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
		set_frames(game, img.shotgun_img_4, img.shotgun_img_0, IDLE);
}
