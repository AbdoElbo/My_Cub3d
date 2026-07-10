/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doors_opening.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:02:25 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/05 16:12:20 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.h"

void look_for_door_coordinates(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'D')
			{
				game->doors[k].x = j;
				game->doors[k].y = i;
				game->doors[k].open = false;
				k++;
			}
			j++;
		}
		i++;
	}
	return ;
}

int init_doors(t_game *game)
{
	t_door *doors;

	doors = NULL;
	if (game->door_count > 0)
	{
		doors = malloc(sizeof(t_door) * game->door_count);
		if (!game->doors)
		{
			printf("Door malloc error.\n");
			return(0);
		}
	}
	game->doors = doors;
	look_for_door_coordinates(game);
	// make_doors_solid(game);
	return (1);
}
