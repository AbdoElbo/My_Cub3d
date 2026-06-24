/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:58 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/23 20:53:05 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"

static uint32_t tile_color(char c)
{
	if (c == '1')
		return (get_rgb_color(0, 0, 200));
	if (c == '0')
		return (get_rgb_color(0, 200, 0));
	return (get_rgb_color(20, 20, 20));
}

static void	draw_tile(t_game *game, int px, int py, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(game->mm_img, px + j, py + i, color);
			j++;
		}
		i++;
	}
}


static void	draw_circle(t_game *game, int cx, int cy, int r, uint32_t color)
{
	int	dx;
	int	dy;

	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx < r)
		{
			if (dx * dx + dy * dy <= r * r)
				mlx_put_pixel(game->mm_img,
				cx + dx, cy + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game)
{
	char	c;
	int		row;
	int		col;
	int		map_row;
	int		map_col;
	
	row = 0;
	while (row < MINIMAP_SIZE)
	{
		col = 0;
		while (col < MINIMAP_SIZE)
		{
			map_row = (int)game->player.y - RADIUS + row;
			map_col = (int)game->player.x - RADIUS + col;
			if (map_row < 0 || map_row >= game->height
				|| map_col < 0 || map_col >= game->width)
				c = ' ';
			else
				c = game->map[map_row][map_col];
			draw_tile(game, col * TILE_SIZE, row * TILE_SIZE, tile_color(c));
			col++;
		}
		row++;
	}
	draw_circle(game, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, 4, get_rgb_color(100, 50, 30));
}