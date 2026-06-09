/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:25:46 by gekko             #+#    #+#             */
/*   Updated: 2026/06/09 19:58:47 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

static void	recursive(char **map, int row, int col, int height, int width)
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
	recursive(game->map, 0, 0, game->height + 1, game->width);
	counter_after = comp_counter(game->map);
	if (counter_before != counter_after)
		return(false);
	return (true);
}

static bool check_surroundings(char **str, int index_i, int index_j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = str[index_i - 1][index_j];
	down = str[index_i + 1][index_j];
	left = str[index_i][index_j - 1];
	right = str[index_i][index_j + 1];
	if (up != '1' && up != '0' && up != 'N' && up != 'W'
		&& up != 'E' && up != 'S')
		return (false);
	if (down != '1' && down != '0' && down != 'N' && down != 'W'
		&& down != 'E' && down != 'S')
		return (false);
	if (left != '1' && left != '0' && left != 'N' && left != 'W'
		&& left != 'E' && left != 'S')
		return (false);
	if (right != '1' && right != '0' && right != 'N' && right != 'W'
		&& right != 'E' && right != 'S')
		return (false);
	return (true);
}

bool	check_inside(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 1;
		while(str[i][j])
		{
			if (str[i][j] == '0' || str[i][j] == 'N' || str[i][j] == 'W'
				|| str[i][j] == 'E' || str[i][j] == 'S')
			{
				if (!check_surroundings(str, i, j))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
