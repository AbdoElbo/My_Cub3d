/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/19 17:38:49 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

void	ft_hook(void *param)
{
	t_game		*game;

	game = (t_game *)param;
	update_minimap(game);
	draw_minimap(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forwards(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backwards(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
}

int	load_map_and_components(t_game *game)
{
	game->mlx = mlx_init(MAX_WIDTH, MAX_HEIGHT, "Our Awesome Game", 1);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	game->img = mlx_new_image(game->mlx, MINIMAP_HEIGHT, MINIMAP_WIDTH);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	return (1);
}

void	print_map(t_game *game)
{
	printf("\nPRINTING THE MAP:\n");
	for(int i = 0; game->map[i]; i++)
		printf("%s\n", game->map[i]);
	printf("\nPlayer at X= %f, Y= %f\n", game->player.x, game->player.y);
	printf("and his direction is :%c\n", game->player.dir_char);
}

void	print_2array(char **arr)
{
	printf("\nPRINTING THE 2ARRAY:\n");
	for(int i = 0; arr[i]; i++)
		printf("%s\n", arr[i]);
}

// static void	print_stuff(t_game *game)
// {
// 	printf("Floor:'0x%08X'\n", game->floor_color);
// 	printf("Ceiling:'0x%08X'\n\n", game->ceiling_color);
// 	printf("North:'%s'\n", game->files.north);
// 	printf("East:'%s'\n", game->files.east);
// 	printf("West:'%s'\n", game->files.west);
// 	printf("South:'%s'\n", game->files.south);
// 	printf("map_start at %d\n\n", game->map_start);
// 	printf("map height is %d\n", game->height);
// 	printf("map width is %d\n", game->width);
// }

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!init_map(argc, argv[1], &game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!map_validity(&game))
		return (cleanup(&game), EXIT_FAILURE);
	print_map(&game);
	if (!make_plane(&game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!load_map_and_components(&game))
		return (cleanup(&game), EXIT_FAILURE);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), EXIT_SUCCESS);
}
