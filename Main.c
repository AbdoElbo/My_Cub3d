/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/14 15:31:03 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

void	ft_hook(void *param)
{
	t_game	*game;
	int		off_x;
	int		off_y;
	static int e_was_down;
	int		e_is_down;

	game = (t_game *)param;
	off_x = (int)((game->player.x - (int)game->player.x) * TILE_SIZE);
	off_y = (int)((game->player.y - (int)game->player.y) * TILE_SIZE);
	cast_rays(game);
	render_frame(game);
	draw_minimap(game, off_x, off_y);
	test_sprite_loop(game);
	draw_minimap(game, off_x, off_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	// printf("frame is rendered\n");
	move_player(game);
	rotate_player(game);
	gun_dev(game);
	e_is_down = mlx_is_key_down(game->mlx, MLX_KEY_E);
	if (e_is_down && !e_was_down)
		open_close_door(game);
	e_was_down = e_is_down;
	// if (mlx_is_key_down(game->mlx, MLX_KEY_1))
	// 	set_animation(&game->enemy.sprite, ANIM_WALK);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_2))
	// 	set_animation(&game->enemy.sprite, ANIM_HURT);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_3))
	// 	set_animation(&game->enemy.sprite, ANIM_ATTACK);
	// if (mlx_is_key_down(game->mlx, MLX_KEY_4))
	// 	set_animation(&game->enemy.sprite, ANIM_DEATH);
}

int	load_map_and_components(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Our Awesome Game", 1);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->framebuf = mlx_new_image(game->mlx, MAX_WIDTH, MAX_HEIGHT);
	mlx_image_to_window(game->mlx, game->framebuf, 0, 0);
	game->mm_img = mlx_new_image(game->mlx, MINIMAP_PX, MINIMAP_PX);
	if (!game->mm_img)
		return (printf("Error:\nMlx img_mm creation failed\n"), 0);
	if (mlx_image_to_window(game->mlx, game->mm_img, 0, 0))
		return (printf("Error:\nMlx img_mm image_to_window failed\n"), 0);
	game->texture_north = mlx_load_png("Resources/textures/north_texture.png"); // MAKE LOADING OF TEXTURES SAFE
	game->texture_east = mlx_load_png("Resources/textures/east_texture.png");
	game->texture_west = mlx_load_png("Resources/textures/west_texture.png");
	game->texture_south = mlx_load_png("Resources/textures/south_texture.png");
	game->texture_door = mlx_load_png("Resources/textures/door.png");
	// game->img = mlx_new_image(game->mlx, 1000, 1000);
	// mlx_image_to_window(game->mlx, game->img, 0, 0);
	if (!load_sword_tex(game) || !load_other_tex(game))
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
	if (!init_enemy_sprite(&game))
		return (cleanup(&game), EXIT_FAILURE);
	// printf("Map loaded successfully!\n");
	// print_map(&game);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_cursor_hook(game.mlx, ft_mouse_mvm, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), EXIT_SUCCESS);
}
