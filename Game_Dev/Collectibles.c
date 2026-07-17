/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 15:30:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/17 16:13:55 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static void	collectible_coordinates(t_game *game)
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
			if (game->map[i][j] == 'C')
			{
				game->collect[k].x = j + 0.5f;;
				game->collect[k].y = i + 0.5f;;
				game->collect[k].available = true;
				k++;
			}
			j++;
		}
		i++;
	}
}

int	init_collectibles(t_game *game)
{
	t_collect *collect;

	collect = NULL;
	if (game->vars.collect_count > 0)
	{
		collect = malloc(sizeof(t_collect) * game->vars.collect_count);
		if (!collect)
			return(printf("Collectibles malloc error.\n"), 0);
		game->collect = collect;
		collectible_coordinates(game);
	}
	return (1);
}
