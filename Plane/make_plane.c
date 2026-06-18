/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:58 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/18 19:42:23 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"

void	update_minimap(t_game *game) // in the hook
{
	// get the new positions a.k.a update the minimap accordingly
	int	row;
	int	col;
	int	map_row;
	int	map_col;

	row = 0;
	while (row < MINIMAP_SIZE)
	{
		col = 0;
		while (col < MINIMAP_SIZE)
		{
			map_row = (int)game->player.x - RADIUS + row;
			map_col = (int)game->player.y - RADIUS + col;
			if (map_row < 0 || map_row >= game->height ||
				map_col < 0 || map_col >= game->width)
				game->mini[row][col] = ' ';
			else
				game->mini[row][col] = game->map[map_row][map_col];
			col++;
		}
		row++;
	}
}

static void	draw_tile(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while(i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (x + j < (int)game->img->width && y + i < (int)game->img->height)
			{
				if (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1)
					mlx_put_pixel(game->img, x + j, y + i, get_rgb_color(0, 0, 0));
				else
					mlx_put_pixel(game->img, x + j, y + i, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while(i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (game->mini[i][j] == 'W' || game->mini[i][j] == 'N'
				|| game->mini[i][j] == 'E' || game->mini[i][j] == 'S')
				draw_tile(game, j * TILE_SIZE, i * TILE_SIZE, get_rgb_color(250, 0, 0));
			else if (game->mini[i][j] == '1')
				draw_tile(game, j * TILE_SIZE, i * TILE_SIZE, get_rgb_color(0, 250, 0));
			else
				draw_tile(game, j * TILE_SIZE, i * TILE_SIZE, get_rgb_color(0, 0, 250));
			j++;
		}
		i++;
	}
}

static char	**allocate_minimap(void)
{
	int		i;
	int		j;
	char	**minimap;

	i = 0;
	minimap = malloc(sizeof(char *) * (MINIMAP_SIZE + 1));
	if (!minimap)
		return (printf("MALLOC error at allocate_minimap\n"), NULL);
	while(i < MINIMAP_SIZE + 1)
	{
		minimap[i] = ft_calloc((MINIMAP_SIZE + 1), sizeof(char));
		if (!minimap[i])
			return (free_arr(minimap), NULL);
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			minimap[i][j] = '0';
			j++;
		}
		i++;
	}
	minimap[MINIMAP_SIZE] = NULL;
	return (minimap);
}

int	make_plane(t_game *game)
{
	game->mini = allocate_minimap();
	if (!game->mini)
		return (0);
	update_minimap(game);
	print_2array(game->mini);
	return (1);
}
