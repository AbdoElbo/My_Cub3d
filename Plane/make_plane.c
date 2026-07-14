/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:58 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/14 13:09:04 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"

static uint32_t tile_color(t_game *game, char c)
{
	if (c == '1')
		return (get_rgb_color(88, 57, 39));
	return (game->floor_color);
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
					px_color = get_rgb_color(0,0,0);
				else
					px_color = color;
				mlx_put_pixel(game->mm_img, px + j, py + i, px_color);
			}
			j++;
		}
		i++;
	}
}

static void	draw_circle(t_game *game, int r, uint32_t color)
{
	int	dx;
	int	dy;
	int	cx;
	int	cy;

	cx = MINIMAP_PX / 2;
	cy = MINIMAP_PX / 2;
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

static void	draw_floor(t_game *game, int offset_x, int offset_y)
{
	char	c;
	int		row;
	int		col;
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
			if (map_row < 0 || map_row >= game->height
				|| map_col < 0 || map_col >= game->width)
				c = ' ';
			else
				c = game->map[map_row][map_col];
			draw_tile(game, col * TILE_SIZE - offset_x + TILE_SIZE / 2,
				row * TILE_SIZE - offset_y + TILE_SIZE / 2, tile_color(game, c));
			col++;
		}
		row++;
	}
}

void	draw_minimap(t_game *game, int offset_x, int offset_y)
{
	draw_floor(game, offset_x, offset_y);
	draw_circle(game, 3, get_rgb_color(255, 100, 0));
	// draw_line(game, game->rays, get_rgb_color(0, 200, 0));
}
