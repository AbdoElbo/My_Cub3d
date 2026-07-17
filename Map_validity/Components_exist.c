/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Components_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:26:19 by gekko             #+#    #+#             */
/*   Updated: 2026/07/17 15:40:45 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

int	player_exists(t_game *game)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'W'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'S')
			{
				found++;
				game->player.y = i + 0.5f;
				game->player.x = j + 0.5f;
				game->player.dir_char = game->map[i][j];
				game->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (found);
}

int	comp_counter(char **map)
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
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'D'
				|| map[i][j] == 'V' || map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
