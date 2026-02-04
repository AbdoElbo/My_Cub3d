/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/04 14:05:38 by aelbouaz         ###   ########.fr       */
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
	game->mlx = mlx_init(1000, 500, "My Awesome Game 🦎", 0);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	game->img = mlx_new_image(game->mlx, 1000, 500);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			mlx_put_pixel(game->img, i, j, game->floor_color);
	}
	for (int i = 500; i < 1000; i++)
	{
		for (int j = 0; j < 500; j++)
			mlx_put_pixel(game->img, i, j, game->ceiling_color);
	}
	return (1);
}

static void	print_stuff(t_game *game)
{
	printf("North:'%s'\n", game->files.north);
	printf("East:'%s'\n", game->files.east);
	printf("West:'%s'\n", game->files.west);
	printf("South:'%s'\n\n", game->files.south);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!init_map(argc, argv[1], &game))
		return (1);
	load_map_and_components(&game);
	print_stuff(&game);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), 0);
}
