/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/23 17:51:41 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

static int	display_coins_acquired(t_game *game)
{
	char	*c_num;
	char	*hp_num;

	c_num = ft_itoa(game->vars.collect_count);
	if (!c_num)
		return (0);
	ft_memcpy(&game->collect_str[23], c_num, ft_strlen(c_num));
	free(c_num);
	if (game->images.collect_text)
		mlx_delete_image(game->mlx, game->images.collect_text);
	game->images.collect_text = mlx_put_string(game->mlx, game->collect_str
		, MINIMAP_PX + 10, 20);
	mlx_set_instance_depth(game->images.collect_text->instances, 1);

	hp_num = ft_itoa(game->player.health);
	if (!hp_num)
		return (0);
	ft_memcpy(&game->player_hp_str[13], hp_num, ft_strlen(hp_num));
	free(hp_num);
	if (game->images.player_hp_text)
		mlx_delete_image(game->mlx, game->images.player_hp_text);
	game->images.player_hp_text = mlx_put_string(game->mlx, game->player_hp_str
		, MINIMAP_PX + 10, 40);
	mlx_set_instance_depth(game->images.player_hp_text->instances, 30);
	return (1);
}

static void	ft_open_door(t_game *game)
{
	static int	e_was_down;
	int			e_is_down;

	e_is_down = mlx_is_key_down(game->mlx, MLX_KEY_E);
	if (e_is_down && !e_was_down)
		open_close_door(game);
	e_was_down = e_is_down;
}

static void	delete_blood(t_game *game)
{
	long long	now;
	long long	frame_duration;
	mlx_image_t	*img;

	img = game->images.getting_hurt;
	frame_duration = 500;
	now = get_time_in_ms();
	if (now - game->vars.last_hit < frame_duration)
		return ;
	game->images.getting_hurt->enabled = false;
	game->vars.last_hit = 0;
}

void	ft_hook(void *param)
{
	t_game	*game;
	int		i;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (game->player.health)
	{
		cast_rays(game);
		render_frame(game);
		draw_minimap(game);
		i = 0;
		rotate_player(game);
		while (i < game->vars.enemy_count)
			render_enemy(game, &game->enemy[i++]);
		move_player(game);
		move_enemies(game);
		gun_dev(game);
		ft_open_door(game);
		delete_blood(game);
		if (!display_coins_acquired(game))
			return ;
	}
	else
		game->images.death->enabled = 1;
}

int	allocate_text(t_game *game)
{
	game->collect_str = ft_calloc(40, sizeof(char));
	if (!game->collect_str)
		return (printf("Error:\ngame->collect_str allocation failed\n"), 0);
	game->player_hp_str = ft_calloc(40, sizeof(char));
	if (!game->player_hp_str)
		return (printf("Error:\ngame->player_hp_str allocation failed\n"), 0);
	ft_strlcpy(game->collect_str, "Collectibles obtained: ", 25);
	ft_strlcpy(game->player_hp_str, "Player's HP: ", 15);
	return (1);
}

int	load_map_and_components(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Our Awesome Game", 1);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->framebuf = mlx_new_image(game->mlx, MAX_WIDTH, MAX_HEIGHT);
	mlx_image_to_window(game->mlx, game->framebuf, 0, 0);
	game->images.mm_img = mlx_new_image(game->mlx, MINIMAP_PX, MINIMAP_PX);
	if (!game->images.mm_img)
		return (printf("Error:\nMlx img_mm creation failed\n"), 0);
	if (mlx_image_to_window(game->mlx, game->images.mm_img, 0, 0))
		return (printf("Error:\nMlx img_mm image_to_window failed\n"), 0);
	if (!load_compass_tex(game))
		return (0);
	if (!load_gun_tex(game))
		return (0);
	if (!allocate_text(game))
		return (0);
	return (1);
}

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
	// printf("Map loaded successfully!\n");
	// print_map(&game);
	mlx_loop_hook(game.mlx, &ft_hook, &game);
	mlx_cursor_hook(game.mlx, ft_mouse_mvm, &game);
	mlx_loop(game.mlx);
	return (cleanup(&game), EXIT_SUCCESS);
}
