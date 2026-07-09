/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 18:29:27 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/09 18:39:22 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

int	load_pistol_tex(t_game *game)
{
	game->textures.pistol_tex_0 = mlx_load_png("./Resources/textures/pistol_idle.png");
	if (!game->textures.pistol_tex_0)
		return (printf("pistol Tex didn't Load"), 0);
	game->images.pistol_img_0 = mlx_texture_to_image(game->mlx, game->textures.pistol_tex_0);
	if (!game->images.pistol_img_0)
		return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.pistol_tex_1 = mlx_load_png("./Resources/textures/pistol_1.png");
	// if (!game->textures.pistol_tex_1)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.pistol_img_1 = mlx_texture_to_image(game->mlx, game->textures.pistol_tex_1);
	// if (!game->images.pistol_img_1)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.pistol_tex_0 = mlx_load_png("./Resources/textures/pistol_2.png");
	// if (!game->textures.pistol_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.pistol_img_0 = mlx_texture_to_image(game->mlx, game->textures.pistol_tex_0);
	// if (!game->images.pistol_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.pistol_tex_0 = mlx_load_png("./Resources/textures/pistol_3.png");
	// if (!game->textures.pistol_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.pistol_img_0 = mlx_texture_to_image(game->mlx, game->textures.pistol_tex_0);
	// if (!game->images.pistol_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	return (1);
}

int	load_uzi_tex(t_game *game)
{
	(void)game;
	// game->textures.uzi_tex_0 = mlx_load_png("./Resources/textures/uzi_idle.png");
	// if (!game->textures.uzi_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.uzi_img_0 = mlx_texture_to_image(game->mlx, game->textures.uzi_tex_0);
	// if (!game->images.uzi_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.uzi_tex_1 = mlx_load_png("./Resources/textures/uzi_1.png");
	// if (!game->textures.uzi_tex_1)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.uzi_img_1 = mlx_texture_to_image(game->mlx, game->textures.uzi_tex_1);
	// if (!game->images.uzi_img_1)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.uzi_tex_0 = mlx_load_png("./Resources/textures/uzi_2.png");
	// if (!game->textures.uzi_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.uzi_img_0 = mlx_texture_to_image(game->mlx, game->textures.uzi_tex_0);
	// if (!game->images.uzi_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.uzi_tex_0 = mlx_load_png("./Resources/textures/uzi_3.png");
	// if (!game->textures.uzi_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.uzi_img_0 = mlx_texture_to_image(game->mlx, game->textures.uzi_tex_0);
	// if (!game->images.uzi_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	return (1);
}

int	load_ak47_tex(t_game *game)
{
	(void)game;
	// game->textures.ak47_tex_0 = mlx_load_png("./Resources/textures/ak47_idle.png");
	// if (!game->textures.ak47_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.ak47_img_0 = mlx_texture_to_image(game->mlx, game->textures.ak47_tex_0);
	// if (!game->images.ak47_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.ak47_tex_1 = mlx_load_png("./Resources/textures/ak47_1.png");
	// if (!game->textures.ak47_tex_1)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.ak47_img_1 = mlx_texture_to_image(game->mlx, game->textures.ak47_tex_1);
	// if (!game->images.ak47_img_1)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.ak47_tex_0 = mlx_load_png("./Resources/textures/ak47_2.png");
	// if (!game->textures.ak47_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.ak47_img_0 = mlx_texture_to_image(game->mlx, game->textures.ak47_tex_0);
	// if (!game->images.ak47_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	// game->textures.ak47_tex_0 = mlx_load_png("./Resources/textures/ak47_3.png");
	// if (!game->textures.ak47_tex_0)
	// 	return (printf("pistol Tex didn't Load"), 0);
	// game->images.ak47_img_0 = mlx_texture_to_image(game->mlx, game->textures.ak47_tex_0);
	// if (!game->images.ak47_img_0)
	// 	return (printf("Pistol tex wasn't converted to image"), 0);
	return (1);
}
