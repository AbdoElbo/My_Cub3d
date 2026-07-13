/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:29:27 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/13 19:31:12 by aelbouaz         ###   ########.fr       */
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

static int	load_images(t_game *game, char *path
		, mlx_texture_t **tex, mlx_image_t **img)
{
	int	x_pos;
	int	y_pos;

	*tex = mlx_load_png(path);
	if (!*tex)
		return (printf("Texture didn't load: %s\n", path), 0);
	*img = mlx_texture_to_image(game->mlx, *tex);
	mlx_delete_texture(*tex); // im deleting tex before checking for img so in case of conversion failure, tex will always be deleted ...
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

int	load_sword_tex(t_game *game)
{
	if (!load_images(game, "./Resources/textures/sword_0.png",
			&game->textures.sword_tex_0, &game->images.sword_img_0))
		return (0);
	if (!load_images(game, "./Resources/textures/sword_1.png",
			&game->textures.sword_tex_1, &game->images.sword_img_1))
		return (0);
	if (!load_images(game, "./Resources/textures/sword_2.png",
			&game->textures.sword_tex_2, &game->images.sword_img_2))
		return (0);
	if (!load_images(game, "./Resources/textures/sword_3.png",
			&game->textures.sword_tex_3, &game->images.sword_img_3))
		return (0);
	if (!load_images(game, "./Resources/textures/sword_4.png",
			&game->textures.sword_tex_4, &game->images.sword_img_4))
		return (0);
	return (1);
}

int	load_other_tex(t_game *game)
{
	if (!load_images(game, "./Resources/textures/other_0.png",
			&game->textures.other_tex_0, &game->images.other_img_0))
		return (0);
	if (!load_images(game, "./Resources/textures/other_1.png",
			&game->textures.other_tex_1, &game->images.other_img_1))
		return (0);
	if (!load_images(game, "./Resources/textures/other_2.png",
			&game->textures.other_tex_2, &game->images.other_img_2))
		return (0);
	if (!load_images(game, "./Resources/textures/other_3.png",
			&game->textures.other_tex_3, &game->images.other_img_3))
		return (0);
	if (!load_images(game, "./Resources/textures/other_4.png",
			&game->textures.other_tex_4, &game->images.other_img_4))
		return (0);
	return (1);
}
