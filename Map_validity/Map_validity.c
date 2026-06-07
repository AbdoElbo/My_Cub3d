/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:38:34 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/08 01:15:48 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

static bool	player_exists(char **map)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' 
				|| map[i][j] == 'E' || map[i][j] == 'S')
				found++;
			j++;
		}
		i++;
	}
	if (found == 1)
		return (true);
	else if (found > 1)
		return (printf("ERROR, Multiple players found! Exiting..."), false);
	return (printf("ERROR, No Player Found! Exiting..."), false);
}

static void    flood_fill(char **map, int row, int col, int height, int width)
{
    if (row < 0 || row >= height || col < 0 || col >= width)
        return ;
    if (map[row][col] != '1')
        return ;
    map[row][col] = 'X';
    flood_fill(map, row - 1, col, height, width);
    flood_fill(map, row + 1, col, height, width);
    flood_fill(map, row, col - 1, height, width);
    flood_fill(map, row, col + 1, height, width);
}

static int	counter(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'W' 
				|| map[i][j] == 'E' || map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static bool	flood_fill_outside(t_game *game)
{
	int	counter_before;
	int	counter_after;
	
	counter_before = counter(game->map);
	flood_fill(game->map, game->map_start, 0, game->height, game->width);
	counter_after = counter(game->map);
	if (counter_before != counter_after)
		return(printf("LOL, MAP IS NOT FULLY CLOSED (outside flood_fill)"), false);
	return (true);
}

int	map_validity(t_game *game)
{
	if (!player_exists(&game->map[game->map_start]))
		return (0);
	if (!flood_fill_outside(game))
		return (0);
	// check if only on player is present
	// check if one of the islands is open
	// 
	return (1);
}
