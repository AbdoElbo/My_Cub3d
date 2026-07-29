/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 13:27:37 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/29 13:40:06 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

static int	display_coins_text(t_game *game)
{
	char	*num_str;

	num_str = ft_itoa(game->vars.obtained_coins);
	if (!num_str)
		return (0);
	ft_memcpy(&game->collect_str[23], num_str, ft_strlen(num_str));
	game->collect_str[23 + ft_strlen(num_str)] = '\0';
	free(num_str);
	if (game->images.collect_text)
		mlx_delete_image(game->mlx, game->images.collect_text);
	game->images.collect_text = mlx_put_string(game->mlx, game->collect_str
		, MINIMAP_PX + 10, 20);
	mlx_resize_image(game->images.collect_text, game->images.collect_text->width * 1.5, game->images.collect_text->height * 1.5);
	mlx_set_instance_depth(game->images.collect_text->instances, 30);
	return (1);
}

static int	display_health_text(t_game *game)
{
	char	*num_str;

	num_str = ft_itoa(game->player.health);
	if (!num_str)
		return (0);
	ft_memcpy(&game->player_hp_str[13], num_str, ft_strlen(num_str));
	game->player_hp_str[13 + ft_strlen(num_str)] = '\0';
	free(num_str);
	if (game->images.player_hp_text)
		mlx_delete_image(game->mlx, game->images.player_hp_text);
	game->images.player_hp_text = mlx_put_string(game->mlx, game->player_hp_str
		, MINIMAP_PX + 10, 60);
	mlx_resize_image(game->images.player_hp_text, game->images.player_hp_text->width * 1.5, game->images.player_hp_text->height * 1.5);
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
		if (!display_coins_text(game) || !display_health_text(game))
			return ;
		cast_rays(game);
		render_frame(game);
		draw_minimap(game);
		rotate_player(game);
		move_player(game);
		gun_dev(game);
		ft_open_door(game);
		i = 0;
		while (i < game->vars.enemy_count)
			render_enemy(game, &game->enemy[i++]);
		move_enemies(game);
		delete_blood(game);
	}
	else
		game->images.death->enabled = 1;
}
