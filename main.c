/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/28 20:22:25 by aelbouaz         ###   ########.fr       */
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
	mlx_image_t	*img;

	game->mlx = mlx_init(500, 500, "My Awesome Game 🦎", 0);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed"), 0);
	img = mlx_new_image(game->mlx, 500, 500);
	mlx_image_to_window(game->mlx, img, 0, 0);
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			mlx_put_pixel(img, i, j, game->floor_color);
	}
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
	printf("north:'%s'\n", game.files.north);
	printf("east:'%s'\n", game.files.east);
	printf("west:'%s'\n", game.files.west);
	printf("south:'%s'\n", game.files.south);
	printf("ceiling:'%u'\n", game.ceiling_color);
	printf("floor:'%u'\n", game.floor_color);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), 0);
}
