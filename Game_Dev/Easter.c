/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:55:18 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/27 15:18:41 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static void	scale_image(mlx_image_t **img)
{
	double	scale_x;
	double	scale_y;
	double	scale;

	scale_x = (double)SCREEN_WIDTH / (*img)->width;
	scale_y = (double)SCREEN_HEIGHT / (*img)->height;
	scale = fmin(scale_x, scale_y);
	mlx_resize_image((*img), (*img)->width * scale, (*img)->height * scale);
}

static int	load_endgame_images(t_game *game, char *path
		, mlx_texture_t **tex, mlx_image_t **img)
{
	int	x_pos;
	int	y_pos;

	*tex = NULL;
	*img = NULL;
	*tex = mlx_load_png(path);
	if (!*tex)
		return (printf("Texture didn't load: %s\n", path), 0);
	*img = mlx_texture_to_image(game->mlx, *tex);
	mlx_delete_texture(*tex); // im deleting tex before checking for img so in case of conversion failure, tex will always be deleted ...
	if (!*img)
		return (printf("Texture wasn't converted to image: %s\n", path), 0);
	scale_image(img);
	x_pos = SCREEN_WIDTH / 2 - ((*img)->width / 2);
	y_pos = SCREEN_HEIGHT / 2 - ((*img)->height / 2);
	if (mlx_image_to_window(game->mlx, *img, x_pos, y_pos))
		return (printf("Error:\nMlx image_to_window failed\n"), 0);
	(*img)->enabled = false;
	return (1);
}

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
	mlx_resize_image(game->images.getting_hurt, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->images.getting_hurt->instances->x = 0;
	game->images.getting_hurt->instances->y = 0;
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
	if (!load_endgame_images(game, "./Resources/textures/death.png",
			&game->textures.death, &game->images.death))
		return (0);
	if (!load_endgame_images(game, "./Resources/textures/win.png",
			&game->textures.win, &game->images.win))
		return (0);
	return (1);
}
