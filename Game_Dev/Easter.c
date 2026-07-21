/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:55:18 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/21 17:09:58 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static int	load_fish_tex(t_game *game)
{
	if (!load_gun_images(game, "./Resources/textures/fish_0.png",
			&game->textures.sword_tex_0, &game->images.sword_img_0))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/fish_1.png",
			&game->textures.sword_tex_1, &game->images.sword_img_1))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/fish_2.png",
			&game->textures.sword_tex_2, &game->images.sword_img_2))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/fish_3.png",
			&game->textures.sword_tex_3, &game->images.sword_img_3))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/fish_4.png",
			&game->textures.sword_tex_4, &game->images.sword_img_4))
		return (0);
	return (1);
}

static int	load_nokia_tex(t_game *game)
{
	if (!load_gun_images(game, "./Resources/textures/nokia_0.png",
			&game->textures.shotgun_tex_0, &game->images.shotgun_img_0))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/nokia_1.png",
			&game->textures.shotgun_tex_1, &game->images.shotgun_img_1))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/nokia_2.png",
			&game->textures.shotgun_tex_2, &game->images.shotgun_img_2))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/nokia_3.png",
			&game->textures.shotgun_tex_3, &game->images.shotgun_img_3))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/nokia_4.png",
			&game->textures.shotgun_tex_4, &game->images.shotgun_img_4))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/getting_hurt.png",
			&game->textures.getting_hurt, &game->images.getting_hurt))
		return (0);
	return (1);
}

int	load_gun_tex(t_game *game)
{
	if (!game->vars.easter_egg)
	{
		if (!load_sword_tex(game) || !load_shotgun_tex(game))
			return (0);
	}
	else
	{
		if (!load_fish_tex(game) || !load_nokia_tex(game))
			return (0);
	}
	return (1);
}
