/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exit_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:02:25 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/27 12:20:59 by lpieck           ###   ########.fr       */
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

void	look_for_exit_coordinates(t_game *game)
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
			if (game->map[i][j] == 'e')
			{
				game->exit[k].x = j;
				game->exit[k].y = i;
				k++;
			}
			j++;
		}
		i++;
	}
	return ;
}

int	init_exit(t_game *game)
{
	t_door *doors;

	doors = NULL;
	if (game->vars.door_count > 0)
	{
		doors = malloc(sizeof(t_door) * game->vars.exit_count);
		if (!doors)
			return(printf("Door malloc error.\n"), 0);
		game->doors = doors;
		look_for_exit_coordinates(game);
	}
	return (1);
}
