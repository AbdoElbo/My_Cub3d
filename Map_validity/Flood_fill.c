/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:25:46 by gekko             #+#    #+#             */
/*   Updated: 2026/06/09 15:38:35 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

static void	recursive(char **map, int row, int col, int height, int width, t_game *game)
	{
	if (row < 0 || row >= height || col < 0 || col >= width)
		return ;
	if (map[row][col] == '1' || map[row][col] == '.')
		return ;
	map[row][col] = '.';
	recursive(map, row, col - 1, height, width, game);
	recursive(map, row, col + 1, height, width, game);
	recursive(map, row + 1, col, height, width, game);
	recursive(map, row - 1, col, height, width, game);
}

bool	flood_fill_outside(t_game *game)
{
	int	counter_before;
	int	counter_after;

	counter_before = comp_counter(game->map);
	recursive(game->map, 0, 0, game->height + 1, game->width, game);
	counter_after = comp_counter(game->map);
	if (counter_before != counter_after)
		return(printf("LOL, MAP IS NOT FULLY CLOSED (outside flood_fill)"), false);
	return (true);
}

// static bool	flood_fill_inside(t_game *game)
// {

// }
