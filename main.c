/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 20:01:15 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// void	ft_hook(void *param)
// {
// 	t_game		*game;

// 	game = (t_game *)param;
// 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(game->mlx);
// }

void	cleanup(t_map **map, t_game *game)
{
	free_map(map);
	close(game->fd);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	*map;

	map = NULL;
	if (!init_map(argc, argv[1], &game, &map))
		return (1);
	/*
		INSET CODE HERE
	*/
	return (cleanup(&map, &game), 0);
}
