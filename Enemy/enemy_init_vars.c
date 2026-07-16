/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:24:39 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/16 15:26:27 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"
#include "../Cubed.h"
//INITIALIZE ENEMY

static t_enemy assign_values_to_enemy(int x, int y)
{
	t_enemy new_enemy;

	new_enemy.x = x + 0.5f;
	new_enemy.y = y + 0.5f;
	new_enemy.health = 3;
	new_enemy.damage = 1;
	new_enemy.sprite.sheet = NULL;
	new_enemy.sprite.frames = NULL;
	return(new_enemy);
}

static void	look_for_enemy_coordinates(t_game *game)
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
			if (game->map[i][j] == 'V')
			{
				// if (k >= game->vars.enemy_count)
				// 	return ;
				game->enemy[k] = assign_values_to_enemy(j, i);
				game->map[i][j] = '0';
				k++;
			}
			j++;
		}
		i++;
	}
}

int	init_enemy(t_game *game)
{
	printf("Amount of enemies: %d\n", game->vars.enemy_count);
	if (game->vars.enemy_count == 0)
	{
		game->enemy = NULL;
		return (1);
	}
	game->enemy = ft_calloc(game->vars.enemy_count, sizeof(t_enemy));
	if (!game->enemy)
		return (0);
	look_for_enemy_coordinates(game);
	return (1);
}
