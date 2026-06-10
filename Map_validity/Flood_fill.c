/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:25:46 by gekko             #+#    #+#             */
/*   Updated: 2026/06/10 15:14:27 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

static void	recursive(t_game *game, int row, int col, int height)
	{
	if (row >= height || col >= game->width
		|| row < 0 || col < 0)
		return ;
	if (game->map[row][col] == '1' || game->map[row][col] == '.')
		return ;
	game->map[row][col] = '.';
	recursive(game, row, col - 1, height);
	recursive(game, row, col + 1, height);
	recursive(game, row + 1, col, height);
	recursive(game, row - 1, col, height);
}

int	flood_fill_outside(t_game *game)
{
	int	counter_before;
	int	counter_after;

	counter_before = comp_counter(game->map);
	recursive(game, 0, 0, game->height + 1);
	counter_after = comp_counter(game->map);
	if (counter_before != counter_after)
		return (false);
	return (true);
}

static int	check_surroundings(char **str, int index_i, int index_j)
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

int	check_inside(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 1;
		while (str[i][j])
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
