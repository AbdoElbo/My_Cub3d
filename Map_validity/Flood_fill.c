/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:25:46 by gekko             #+#    #+#             */
/*   Updated: 2026/06/08 18:35:37 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

static void    recursive(char **map, int row, int col, int height, int width)
{
    if (row < 0 || row >= height || col < 0 || col >= width)
        return ;
    if (map[row][col] == '1' || map[row][col] == '.')
        return ;
    map[row][col] = '.';
    recursive(map, row, col - 1, height, width);
    recursive(map, row, col + 1, height, width);
    recursive(map, row + 1, col, height, width);
    recursive(map, row - 1, col, height, width);
}

bool	flood_fill_outside(t_game *game)
{
	int	counter_before;
	int	counter_after;
	
	counter_before = comp_counter(game->map);
	recursive(game->map, 0, 0, game->height, game->width);
	counter_after = comp_counter(game->map);
	// printf("COUNTER BEFORE : %d\n", counter_before);
	// printf("COUNTER AFTER : %d\n", counter_after);
	if (counter_before != counter_after)
		return(printf("LOL, MAP IS NOT FULLY CLOSED (outside flood_fill)"), false);
	return (true);
}

// static bool	flood_fill_inside(t_game *game)
// {
	
// }