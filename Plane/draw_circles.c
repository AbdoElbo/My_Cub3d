/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 14:15:31 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 14:30:50 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"

void	draw_player_circle(t_game *game, int r, uint32_t color)
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
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				mlx_put_pixel(game->images.mm_img,
					cx + dx, cy + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_enemy_circle(t_game *game, int r, double ex, double ey)
{
	int	dx;
	int	dy;
	int	cx;
	int	cy;

	cx = (int)((ex - game->player.x) * TILE_SIZE) + MINIMAP_PX / 2;
	cy = (int)((ey - game->player.y) * TILE_SIZE) + MINIMAP_PX / 2;
	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
			{
				if (cx + dx >= 0 && cx + dx < MINIMAP_PX
					&& cy + dy >= 0 && cy + dy < MINIMAP_PX)
					mlx_put_pixel(game->images.mm_img,
						cx + dx, cy + dy, get_rgb_color(251, 43, 43));
			}
			dx++;
		}
		dy++;
	}
}

void	draw_collect_circle(t_game *game, int r, double ex, double ey)
{
	int	dx;
	int	dy;
	int	cx;
	int	cy;

	cx = (int)((ex - game->player.x) * TILE_SIZE) + MINIMAP_PX / 2;
	cy = (int)((ey - game->player.y) * TILE_SIZE) + MINIMAP_PX / 2;
	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
			{
				if (cx + dx >= 0 && cx + dx < MINIMAP_PX
					&& cy + dy >= 0 && cy + dy < MINIMAP_PX)
					mlx_put_pixel(game->images.mm_img,
						cx + dx, cy + dy, get_rgb_color(251, 223, 43));
			}
			dx++;
		}
		dy++;
	}
}
