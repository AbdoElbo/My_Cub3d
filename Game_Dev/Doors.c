/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:02:25 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/17 16:03:51 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

int	load_images(t_game *game, char *path
		, mlx_texture_t **tex, mlx_image_t **img)
{
	*tex = NULL;
	*tex = mlx_load_png(path);
	if (!*tex)
	{
		*tex = NULL;
		return (printf("Texture didn't load: %s\n", path), 0);
	}
	*img = NULL;
	*img = mlx_texture_to_image(game->mlx, *tex);
	if (!*img)
	{
		*img = NULL;
		return (printf("Texture wasn't converted to image: %s\n", path), 0);
	}
	return (1);
}

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
	t_door *doors;

	doors = NULL;
	if (game->vars.door_count > 0)
	{
		doors = malloc(sizeof(t_door) * game->vars.door_count);
		if (!doors)
			return(printf("Door malloc error.\n"), 0);
		game->doors = doors;
		look_for_door_coordinates(game);
	}
	return (1);
}

void	open_close_door(t_game *game)
{
	int i;
	int target_x;
	int target_y;

	target_x = (int)floor(game->player.x + game->player.dir_x * 1);
	target_y = (int)floor(game->player.y + game->player.dir_y * 1);
	i = 0;
	while(i < game->vars.door_count)
	{
		if (game->doors[i].x == target_x && game->doors[i].y == target_y)
		{
			game->doors[i].open = !game->doors[i].open;
			return ;
		}
		i++;
	}
}

int	check_open_door(int map_x, int map_y, t_game *game)
{
	int i;

	i = 0;
	while(i < game->vars.door_count)
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
