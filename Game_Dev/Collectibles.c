/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:30:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 13:57:25 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static void	collectible_coordinates(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'C')
			{
				game->collect[k].x = j + 0.5f;
				game->collect[k].y = i + 0.5f;
				game->collect[k].available = true;
				game->collect[k].index = k;
				k++;
			}
			j++;
		}
		i++;
	}
}

int	init_collectibles(t_game *game)
{
	t_collect	*collect;

	collect = NULL;
	game->vars.obtained_coins = 0;
	if (game->vars.collect_count > 0)
	{
		collect = malloc(sizeof(t_collect) * game->vars.collect_count);
		if (!collect)
			return (printf("Collectibles malloc error.\n"), 0);
		game->collect = collect;
		collectible_coordinates(game);
	}
	return (1);
}

double	get_c_angle_diff(t_game *game, t_collect *collect)
{
	double	render_angle;
	double	angle_diff;

	render_angle = atan2(collect->y - game->player.y,
			collect->x - game->player.x);
	angle_diff = render_angle - game->player.angle;
	while (angle_diff > PI)
		angle_diff -= 2 * PI;
	while (angle_diff < -PI)
		angle_diff += 2 * PI;
	return (angle_diff);
}

int	c_sprite_visible(t_collect *collect, t_player *p,
		double angle_diff, double *depth)
{
	collect->dst_to_player = sqrtf((collect->x - p->x) * (collect->x - p->x)
			+ (collect->y - p->y) * (collect->y - p->y));
	if (angle_diff < -FOV / 2 || angle_diff > FOV / 2)
		return (0);
	if (collect->dst_to_player <= 0.1)
		return (0);
	*depth = collect->dst_to_player * cos(angle_diff);
	if (*depth <= 0.1)
		return (0);
	return (1);
}

// void	render_collectible(t_game *game, t_collect *collect)
// {
// 	double			depth;
// 	double			angle_diff;
// 	mlx_image_t		*frame;
// 	t_projection	projection ;

// 	angle_diff = get_c_angle_diff(game, collect);
// 	if (!c_sprite_visible(collect, &game->player, angle_diff, &depth))
// 		return ;
// 	frame = game->images.collectible_img;
// 	projection = compute_projection(angle_diff, depth, 0.2f, 0.1f);
// 	draw_sprite(game, frame, &projection);
// }

void	render_collectible(t_game *game, t_collect *collect)
{
	double			depth;
	double			angle_diff;
	t_projection	projection;

	if (collect->available)
	{
		angle_diff = get_c_angle_diff(game, collect);
		if (!c_sprite_visible(collect, &game->player, angle_diff, &depth))
			return ;
		collect->img = game->images.collectible_img;
		projection = compute_projection(angle_diff, depth, 0.2f, 0.1f);
		draw_sprite(game, collect->img, &projection);
		if (collect->dst_to_player <= 0.5f)
		{
			game->vars.obtained_coins++;
			collect->available = false;
			collect->img->enabled = 0;
		}
	}
}
