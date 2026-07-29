/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/29 13:29:47 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!init_map(argc, argv, &game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!map_validity(&game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!load_map_and_components(&game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!init_enemy_sprite(&game))
		return (cleanup(&game), EXIT_FAILURE);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_cursor_hook(game.mlx, ft_mouse_mvm, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), EXIT_SUCCESS);
}

// norminette Enemy Game_Dev Main.c Map_validity Parsing Plane Rendering
