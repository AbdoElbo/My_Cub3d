/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 15:17:30 by gekko             #+#    #+#             */
/*   Updated: 2026/07/22 15:43:23 by aelbouaz         ###   ########.fr       */
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
		game->images.shotgun_img_0->enabled = false;
	}
	else
	{
		game->images.shotgun_img_0->enabled = true;
		game->images.sword_img_0->enabled = false;
	}
}

static void	start_attack(t_game *game)
{
	if (game->movement == FREE)
	{
		game->movement = BUSY;
		game->frame = IDLE;
		game->vars.frame_start = get_time_in_ms();
		if (game->weapon == SWORD)
		{
			game->images.sword_img_0->enabled = false;
			game->images.sword_img_1->enabled = true;
		}
		else
		{
			game->images.shotgun_img_0->enabled = false;
			game->images.shotgun_img_1->enabled = true;
		}
	}
}

void	gun_dev(t_game *game)
{
	bool	mouse_down;

	show_weapon(game);
	if (game->movement == FREE)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_1))
			game->weapon = SWORD;
		if (mlx_is_key_down(game->mlx, MLX_KEY_2))
			game->weapon = SHOTGUN;
	}
	mouse_down = mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT);
	if ((mouse_down && !game->vars.mouse_was_down)
		|| mlx_is_key_down(game->mlx, MLX_KEY_SPACE))
		start_attack(game);
	game->vars.mouse_was_down = mouse_down;
	if (game->weapon == SWORD)
		sword_attack(game);
	else
		shotgun_attack(game);
}
