/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/09 18:35:45 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

void	ft_hook(void *param)
{
	t_game	*game;
	int		off_x;
	int		off_y;

	game = (t_game *)param;
	// render_frame(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	move_player(game);
	rotate_player(game);
	off_x = (int)((game->player.x - (int)game->player.x) * TILE_SIZE);
	off_y = (int)((game->player.y - (int)game->player.y) * TILE_SIZE);
	draw_minimap(game, off_x, off_y);
	gun_dev(game);
	// printf("\nplayer x=%f, y=%f\n",game->player.x, game->player.y);
	// printf("player dir_x=%f, dir_y=%f\n",game->player.dir_x, game->player.dir_y);
	printf("Angle is %f\n",game->player.angle);
}


int	load_map_and_components(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Our Awesome Game🔫", 1);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->mm_img = mlx_new_image(game->mlx, MINIMAP_PX, MINIMAP_PX);
	if (!game->mm_img)
		return (printf("Error:\nMlx img_mm creation failed\n"), 0);
	if (mlx_image_to_window(game->mlx, game->mm_img, 0, 0))
		return (printf("Error:\nMlx img_mm image_to_window failed\n"), 0);
	// game->img = mlx_new_image(game->mlx, 1000, 1000);
	// mlx_image_to_window(game->mlx, game->img, 0, 0);
	if (!load_pistol_tex(game) || !load_uzi_tex(game)
		|| !load_ak47_tex(game))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!init_map(argc, argv[1], &game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!map_validity(&game))
		return (cleanup(&game), EXIT_FAILURE);
	if (!load_map_and_components(&game))
		return (cleanup(&game), EXIT_FAILURE);
	// game.ray.texture = mlx_load_png("Resources/textures/north_texture.png"); //FOR TESTING PURPOSES.
	// if (!game.ray.texture)
	// 	printf("NO GOOD.\n");
	game.framebuf = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(game.mlx, game.framebuf, 0, 0);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_cursor_hook(game.mlx, ft_mouse_mvm, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), EXIT_SUCCESS);
}
