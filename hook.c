/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 13:27:37 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/29 15:06:20 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cubed.h"

int	join_three(t_game *game)
{
	char	*num_str;
	char	*temp;

	num_str = ft_itoa(game->vars.obtained_coins);
	if (!num_str)
		return (0);
	ft_memcpy(&game->collect_str[23], num_str, ft_strlen(num_str));
	game->collect_str[23 + ft_strlen(num_str)] = '\0';
	temp = ft_strjoin(game->collect_str, "/");
	free(num_str);
	if (!temp)
		return (0);
	num_str = ft_itoa(game->vars.collect_count);
	if (!num_str)
		return (free(temp), 0);
	free(game->collect_str);
	game->collect_str = ft_strjoin(temp, num_str);
	free(temp);
	free(num_str);
	if (!game->collect_str)
		return (0);
	return (1);
}

static int	display_coins_text(t_game *g)
{
	if (!join_three(g))
		return (0);
	if (g->images.collect_text)
	{
		mlx_delete_image(g->mlx, g->images.collect_text);
	}
	g->images.collect_text = mlx_put_string(g->mlx, g->collect_str, 235, 20);
	mlx_resize_image(g->images.collect_text,
		g->images.collect_text->width * 1.5,
		g->images.collect_text->height * 1.5);
	mlx_set_instance_depth(g->images.collect_text->instances, 30);
	return (1);
}

static int	display_health_text(t_game *g)
{
	char	*num_str;

	num_str = ft_itoa(g->player.health);
	if (!num_str)
		return (0);
	ft_memcpy(&g->player_hp_str[13], num_str, ft_strlen(num_str));
	g->player_hp_str[13 + ft_strlen(num_str)] = '\0';
	free(num_str);
	if (g->images.player_hp_txt)
		mlx_delete_image(g->mlx, g->images.player_hp_txt);
	g->images.player_hp_txt = mlx_put_string(g->mlx, g->player_hp_str, 235, 60);
	mlx_resize_image(g->images.player_hp_txt,
		g->images.player_hp_txt->width * 1.5,
		g->images.player_hp_txt->height * 1.5);
	mlx_set_instance_depth(g->images.player_hp_txt->instances, 30);
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

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (game->player.health && game->vars.ended == 0)
	{
		if (!display_coins_text(game) || !display_health_text(game))
			return ;
		cast_rays(game);
		render_frame(game);
		draw_minimap(game);
		move_player(game);
		gun_dev(game);
		ft_open_door(game);
		render_sprite_queue(game);
		move_enemies(game);
	}
	else if (game->vars.ended == 1)
		game->images.win->enabled = 1;
	else
		game->images.death->enabled = 1;
}
