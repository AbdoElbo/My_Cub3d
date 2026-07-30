/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:02:25 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/27 12:09:06 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

void	look_for_door_coordinates(t_game *game)
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

int	init_doors(t_game *game)
{
	t_door	*doors;

	doors = NULL;
	if (game->vars.door_count > 0)
	{
		doors = malloc(sizeof(t_door) * game->vars.door_count);
		if (!doors)
			return (printf("Door malloc error.\n"), 0);
		game->doors = doors;
		look_for_door_coordinates(game);
	}
	return (1);
}

void	open_close_door(t_game *game)
{
	int	i;
	int	target_x;
	int	target_y;

	target_x = (int)floor(game->player.x + game->player.dir_x * 1);
	target_y = (int)floor(game->player.y + game->player.dir_y * 1);
	i = 0;
	while (i < game->vars.door_count)
	{
		if (game->doors[i].x == target_x && game->doors[i].y == target_y)
		{
			game->doors[i].open = !game->doors[i].open;
			return ;
		}
		i++;
	}
	if (game->map[target_y][target_x] == 'e'
		&& game->vars.obtained_coins == game->vars.collect_count)
		game->vars.ended = true;
	else
		return ;
}

int	check_open_door(int map_x, int map_y, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->vars.door_count)
	{
		if (game->doors[i].x == map_x && game->doors[i].y == map_y)
		{
			if (game->doors[i].open == true)
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	door_is_open(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->vars.door_count)
	{
		if (g->doors[i].x == x && g->doors[i].y == y && g->doors[i].open)
			return (1);
		i++;
	}
	return (0);
}
