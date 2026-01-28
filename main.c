/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/28 13:36:37 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	ft_hook(void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

int	load_map_and_components(t_game *game)
{
	game->mlx = mlx_init(game->width, game->height, "My Awesome Game 🦎", 0);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed"), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!init_map(argc, argv[1], &game))
		return (1);
	// if (!check_map(game.map))
	// 	return (cleanup(&game), 1);
	load_map_and_components(&game);
	printf("north is '%s'\n", game.files.north);
	printf("south is '%s'\n", game.files.south);
	printf("west is '%s'\n", game.files.west);
	printf("east is '%s'\n", game.files.east);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), 0);
}
