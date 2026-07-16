/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:58 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/16 16:30:06 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"

static uint32_t tile_color(t_game *game, char c)
{
	if (c == '1')
		return (get_rgb_color(88, 57, 39));
	if (c == 'D')
		return (get_rgb_color(0, 100, 100));
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
					px_color = get_rgb_color(0,0,0);
				else
					px_color = color;
				mlx_put_pixel(game->images.mm_img, px + j, py + i, px_color);
			}
			j++;
		}
		i++;
	}
}

static void	draw_player_circle(t_game *game, int r, uint32_t color)
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
				mlx_put_pixel(game->images.mm_img,
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
			if (map_row < 0 || map_row >= game->vars.height
				|| map_col < 0 || map_col >= game->vars.width)
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


static void	draw_enemy_circle(t_game *game, int r, double ex, double ey)
{
	int	dx;
	int	dy;
	int	cx;
	int	cy;
	// int	offset_x;
	// int	offset_y;

	// convert enemy world pos to minimap pixel pos
	// same offset logic as the tile grid
	// offset_x = (int)((game->player.x - (int)game->player.x) * TILE_SIZE);
	// offset_y = (int)((game->player.y - (int)game->player.y) * TILE_SIZE);

	// enemy position relative to player, in pixels
	cx = (int)((ex - game->player.x) * TILE_SIZE) + MINIMAP_PX / 2;
	cy = (int)((ey - game->player.y) * TILE_SIZE) + MINIMAP_PX / 2;

	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)  // fix: <= not
		{
			if (dx * dx + dy * dy <= r * r)
			{
				if (cx + dx >= 0 && cx + dx < MINIMAP_PX
					&& cy + dy >= 0 && cy + dy < MINIMAP_PX)
					mlx_put_pixel(game->images.mm_img,
						cx + dx, cy + dy, get_rgb_color(0, 0, 0));
			}
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_game *game, int offset_x, int offset_y)
{
	int	i = 0;

	draw_floor(game, offset_x, offset_y);
	draw_player_circle(game, 3, get_rgb_color(255, 100, 0));
	while(i < game->vars.enemy_count)
	{
		draw_enemy_circle(game, 3, game->enemy[i].x, game->enemy[i].y);
		i++;
	}
}
