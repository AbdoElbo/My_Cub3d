/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 15:17:30 by gekko             #+#    #+#             */
/*   Updated: 2026/07/13 16:12:54 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	show_weapon(t_game *game)
{
	if (game->movement != FREE)
		return ;
	if (game->weapon == SWORD)
	{
		game->images.sword_img_0->enabled = true;
		game->images.other_img_0->enabled = false;
	}
	else
	{
		game->images.other_img_0->enabled = true;
		game->images.sword_img_0->enabled = false;
	}
}

static void	start_attack(t_game *game)
{
	if (game->movement == FREE && game->weapon == SWORD)
	{
		game->movement = BUSY;
		game->frame = IDLE;
		game->frame_start = get_time_in_ms();
		game->images.sword_img_0->enabled = false;
		game->images.sword_img_1->enabled = true;
	}
	else if (game->movement == FREE && game->weapon == OTHER)
	{
		game->movement = BUSY;
		game->frame = IDLE;
		game->frame_start = get_time_in_ms();
		game->images.other_img_0->enabled = false;
		game->images.other_img_1->enabled = true;
	}
}

void	gun_dev(t_game *game)
{
	bool	mouse_down;

	show_weapon(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_1))
		game->weapon = SWORD;
	if (mlx_is_key_down(game->mlx, MLX_KEY_2))
		game->weapon = OTHER;
	mouse_down = mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT);
	if (mouse_down && !game->mouse_was_down)
		start_attack(game);
	game->mouse_was_down = mouse_down;
	if (game->weapon == SWORD)
		sword_attack(game);
	else
		other_attack(game);
}
