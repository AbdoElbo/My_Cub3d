/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Components_exist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:26:19 by gekko             #+#    #+#             */
/*   Updated: 2026/06/09 20:35:14 by aelbouaz         ###   ########.fr       */
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
		while(game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'W'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'S')
			{
				found++;
				game->player.x = i;
				game->player.y = j;
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
				|| map[i][j] == 'E' || map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
