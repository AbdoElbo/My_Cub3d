/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:29:27 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/29 13:54:46 by aelbouaz         ###   ########.fr       */
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
	scale = fmax(scale_x, scale_y);
	mlx_resize_image((*img), (*img)->width * scale, (*img)->height * scale);
}

int	load_gun_images(t_game *game, char *path
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
	mlx_delete_texture(*tex);
	if (!*img)
		return (printf("Texture wasn't converted to image: %s\n", path), 0);
	scale_image(img);
	x_pos = SCREEN_WIDTH - (*img)->width;
	y_pos = SCREEN_HEIGHT - (*img)->height;
	if (mlx_image_to_window(game->mlx, *img, x_pos, y_pos))
		return (printf("Error:\nMlx image_to_window failed\n"), 0);
	(*img)->enabled = false;
	return (1);
}

int	load_compass_tex(t_game *game)
{
	if (!load_images(game, "Resources/textures/north_texture.png",
			&game->textures.north_tex, &game->images.north_img))
		return (0);
	if (!load_images(game, "Resources/textures/west_texture.png",
			&game->textures.west_tex, &game->images.west_img))
		return (0);
	if (!load_images(game, "Resources/textures/south_texture.png",
			&game->textures.south_tex, &game->images.south_img))
		return (0);
	if (!load_images(game, "Resources/textures/east_texture.png",
			&game->textures.east_tex, &game->images.east_img))
		return (0);
	if (!load_images(game, "Resources/textures/door.png",
			&game->textures.door_tex, &game->images.door_img))
		return (0);
	if (!load_images(game, "Resources/textures/collectible.png",
			&game->textures.collectible_tex, &game->images.collectible_img))
		return (0);
	if (!load_images(game, "Resources/textures/exit_door.png",
			&game->textures.exit_door_tex, &game->images.exit_door_img))
		return (0);
	return (1);
}

int	load_sword_tex(t_game *game)
{
	if (!load_gun_images(game, "./Resources/textures/sword_0.png",
			&game->textures.sword_tex_0, &game->images.sword_img_0))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/sword_1.png",
			&game->textures.sword_tex_1, &game->images.sword_img_1))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/sword_2.png",
			&game->textures.sword_tex_2, &game->images.sword_img_2))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/sword_3.png",
			&game->textures.sword_tex_3, &game->images.sword_img_3))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/sword_4.png",
			&game->textures.sword_tex_4, &game->images.sword_img_4))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/crosshair.png",
			&game->textures.crosshair, &game->images.crosshair))
		return (0);
	mlx_resize_image(game->images.crosshair, 100, 100);
	game->images.crosshair->instances->x = (SCREEN_WIDTH / 2) - 50;
	game->images.crosshair->instances->y = (SCREEN_HEIGHT / 2) - 50;
	return (1);
}

int	load_shotgun_tex(t_game *game)
{
	if (!load_gun_images(game, "./Resources/textures/shotgun_0.png",
			&game->textures.shotgun_tex_0, &game->images.shotgun_img_0))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/shotgun_1.png",
			&game->textures.shotgun_tex_1, &game->images.shotgun_img_1))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/shotgun_2.png",
			&game->textures.shotgun_tex_2, &game->images.shotgun_img_2))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/shotgun_3.png",
			&game->textures.shotgun_tex_3, &game->images.shotgun_img_3))
		return (0);
	if (!load_gun_images(game, "./Resources/textures/shotgun_4.png",
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
