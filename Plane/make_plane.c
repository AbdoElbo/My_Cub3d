/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:58 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 15:10:49 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"

static uint32_t	tile_col(t_game *game, char c)
{
	if (c == '1')
		return (get_rgb_color(88, 57, 39));
	if (c == 'D')
		return (get_rgb_color(200, 80, 39));
	if (c == 'e')
		return (get_rgb_color(0, 150, 30));
	return (game->vars.floor_color);
}

static void	draw_tile(t_game *game, int px, int py, uint32_t color)
{
	int			i;
	int			j;
	uint32_t	px_color;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (px + j >= 0 && px + j < MINIMAP_PX
				&& py + i >= 0 && py + i < MINIMAP_PX)
			{
				if (i == 0 || i == TILE_SIZE - 1
					|| j == 0 || j == TILE_SIZE - 1)
					px_color = get_rgb_color(0, 0, 0);
				else
					px_color = color;
				mlx_put_pixel(game->images.mm_img, px + j, py + i, px_color);
			}
			j++;
		}
		i++;
	}
}

static void	draw_floor(t_game *game, int offset_x, int offset_y)
{
	char	c;
	int		row;
	int		col ;
	int		map_row;
	int		map_col;

	row = -1;
	while (row <= MINIMAP_SIZE)
	{
		col = -1;
		while (col <= MINIMAP_SIZE)
		{
			map_row = (int)game->player.y - RADIUS + row;
			map_col = (int)game->player.x - RADIUS + col;
			if (map_row < 0 || map_row >= game->vars.height
				|| map_col < 0 || map_col >= game->vars.width)
				c = ' ';
			else
				c = game->map[map_row][map_col];
			draw_tile(game, col * TILE_SIZE - offset_x + TILE_SIZE / 2,
				row * TILE_SIZE - offset_y + TILE_SIZE / 2, tile_col(game, c));
			col++;
		}
		row++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i;
	int	off_x;
	int	off_y;

	off_x = (int)((game->player.x - (int)game->player.x) * TILE_SIZE);
	off_y = (int)((game->player.y - (int)game->player.y) * TILE_SIZE);
	draw_floor(game, off_x, off_y);
	draw_player_circle(game, 3, get_rgb_color(43, 251, 57));
	i = 0;
	while (i < game->vars.enemy_count)
	{
		if (game->enemy[i].health)
			draw_enemy_circle(game, 3, game->enemy[i].x, game->enemy[i].y);
		i++;
	}
	i = 0;
	while (i < game->vars.collect_count)
	{
		if (game->collect[i].available)
			draw_collect_circle(game, 3, game->collect[i].x,
				game->collect[i].y);
		i++;
	}
}
