/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/07 19:01:35 by aelbouaz         ###   ########.fr       */
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
	game->mlx = mlx_init(1000, 1000, "My Awesome Game 🦎", 1);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	game->img = mlx_new_image(game->mlx, 1000, 1000);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	draw_minimap(game);
	return (1);
}

static void	print_stuff(t_game *game)
{
	printf("Floor:'0x%08X'\n", game->floor_color);
	printf("Ceiling:'0x%08X'\n\n", game->ceiling_color);
	printf("North:'%s'\n", game->files.north);
	printf("East:'%s'\n", game->files.east);
	printf("West:'%s'\n", game->files.west);
	printf("South:'%s'\n", game->files.south);
	printf("map_start at %d\n\n", game->map_start);
	printf("map height is %d\n", game->height);
	printf("map width is %d\n", game->width);
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
