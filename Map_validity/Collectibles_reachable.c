/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collectible_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 00:00:00 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/30 00:00:00 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

static int	coin_counter(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	reach_recursive(char **temp, int row, int col)
{
	if (row < 0 || col < 0 || !temp[row])
		return ;
	if (col >= (int)ft_strlen(temp[row]))
		return ;
	if (temp[row][col] == '1')
		return ;
	if (temp[row][col] == 'X')
		return ;
	temp[row][col] = 'X';
	reach_recursive(temp, row, col - 1);
	reach_recursive(temp, row, col + 1);
	reach_recursive(temp, row + 1, col);
	reach_recursive(temp, row - 1, col);
}

static char	**map_dup(char **map)
{
	char	**dup;
	int		i;
	int		len;

	i = 0;
	while (map[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		dup[i] = malloc(sizeof(char) * (len + 1));
		if (!dup[i])
			return (free_arr(dup), NULL);
		ft_memcpy(dup[i], map[i], len + 1);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

int	collectibles_reachable(t_game *game)
{
	char	**temp;

	if (game->vars.collect_count == 0)
		return (1);

	temp = map_dup(game->map);
	if (!temp)
		return (0);
	reach_recursive(temp, (int)game->player.y, (int)game->player.x);
	if (coin_counter(temp) == 0)
		return (free_arr(temp), 1);
	return (free_arr(temp), 0);
}
