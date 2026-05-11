/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:59:22 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/23 14:16:41 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static uint32_t	get_color(t_game *game, char c)
{
	uint32_t	color;

	color = 0;
	if (c == '1')
		color = game->ceiling_color;
	else if (c == '0')
		color = game->floor_color;
	else if (c == 'P')
		color = get_rgb_color(0, 250, 0);
	return (color);
}

static void	draw_square(t_game *game, char c, int row, int col)
{
	uint32_t	color;
	int			start_x;
	int			start_y;
	int			x;
	int			y;

	color = get_color(game, c);
	start_x = col * game->multiplier;
	start_y = row * game->multiplier;
	x = start_x;
	while (x < start_x + game->multiplier)
	{
		y = start_y;
		while (y < start_y + game->multiplier)
		{
			mlx_put_pixel(game->img, x, y, color);
			y++;
		}
		x++;
	}
}

static int	get_multiplier(t_game *game)
{
	int	size;
	int	mult;

	if (game->width > game->height)
		size = game->width;
	else
		size = game->height;
	mult = MINIMAP_MAX / size;
	if (mult < 2)
		mult = 2;
	if (mult > 30)
		mult = 30;
	return (mult);
}

void	draw_minimap(t_game *game)
{
	char	**str;
	int		row;
	int		col;
	char	c;

	row = game->map_start;
	str = game->map;
	game->multiplier = get_multiplier(game);
	while (str[row])
	{
		col = 0;
		while (str[row][col])
		{
			c = str[row][col];
			if (c == '1' || c == '0' || c == 'P')
				draw_square(game, c, row - game->map_start, col);
			col++;
		}
		row++;
	}
}
