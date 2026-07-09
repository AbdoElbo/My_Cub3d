/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 15:17:30 by gekko             #+#    #+#             */
/*   Updated: 2026/07/09 18:34:45 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static int	show_weapon(t_game *game)
{
	if (mlx_image_to_window(game->mlx, game->images.pistol_img_0, 0, 0))
		return (printf("Error:\nMlx PISTOL image_to_window failed\n"), 0);
	return (1);
}

void	gun_dev(t_game *game)
{
	if (!show_weapon(game))
		return ;
	// if (mlx_is_key_down(game->mlx, MLX_KEY_1))
	// 	get_weapon(game, PISTOL);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_2))
	// 	get_weapon(game, UZI);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_3))
	// 	get_weapon(game, AK47);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_4))
	// 	get_weapon(game, M134);
	// // wait(); // wait for weapon to be ready
	// if (mlx_is_key_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
	// 	shoot_gun(game);
}
