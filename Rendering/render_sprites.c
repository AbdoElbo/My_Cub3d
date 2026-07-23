/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +#+#+#+#+#+   +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 13:34:35 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/23 13:42:56 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

static void	sort_sprite_draws(t_sprite_draw *draws, int count)
{
	int		i;
	int		j;
	t_sprite_draw	current;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (draws[j].depth > draws[i].depth)
			{
				current = draws[i];
				draws[i] = draws[j];
				draws[j] = current;
			}
			j++;
		}
		i++;
	}
}

static void	collect_enemy_draws(t_game *game, t_sprite_draw *draws,
	int *visible_count)
{
	int		i;
	double	angle_diff;
	double	depth;

	i = 0;
	while (i < game->vars.enemy_count)
	{
		game->enemy[i].dst_from_player = sqrtf((game->enemy[i].x - game->player.x)
			* (game->enemy[i].x - game->player.x)
			+ (game->enemy[i].y - game->player.y)
			* (game->enemy[i].y - game->player.y));
		angle_diff = get_angle_diff(game, &game->enemy[i]);
		if (game->enemy[i].health
			&& sprite_visible(&game->enemy[i], angle_diff, &depth))
		{
			draws[*visible_count].kind = SPRITE_ENEMY;
			draws[*visible_count].ptr = &game->enemy[i];
			draws[*visible_count].depth = depth;
			(*visible_count)++;
		}
		i++;
	}
}

static void	collect_collectible_draws(t_game *game, t_sprite_draw *draws,
	int *visible_count)
{
	int		i;
	double	angle_diff;
	double	depth;

	i = 0;
	while (i < game->vars.collect_count)
	{
		angle_diff = get_c_angle_diff(game, &game->collect[i]);
		if (game->collect[i].available
			&& c_sprite_visible(&game->collect[i], &game->player,
				angle_diff, &depth))
		{
			draws[*visible_count].kind = SPRITE_COLLECT;
			draws[*visible_count].ptr = &game->collect[i];
			draws[*visible_count].depth = depth;
			(*visible_count)++;
		}
		i++;
	}
}

static void	render_sorted_draws(t_game *game, t_sprite_draw *draws, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (draws[i].kind == SPRITE_ENEMY)
			render_enemy(game, (t_enemy *)draws[i].ptr);
		else
			render_collectible(game, (t_collect *)draws[i].ptr);
		i++;
	}
}

void	render_sprite_queue(t_game *game)
{
	t_sprite_draw	*draws;
	int			visible_count;

	draws = malloc(sizeof(t_sprite_draw)
		* (game->vars.enemy_count + game->vars.collect_count));
	if (!draws)
		return ;
	visible_count = 0;
	collect_enemy_draws(game, draws, &visible_count);
	collect_collectible_draws(game, draws, &visible_count);
	sort_sprite_draws(draws, visible_count);
	render_sorted_draws(game, draws, visible_count);
	free(draws);
}
