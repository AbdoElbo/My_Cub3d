/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/10/06 13:08:36 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	ft_hook(void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

int	init_map(int argc, char *argv, t_game *game, char **map)
{
	// char	*map_copy;

	(void)game;
	(void)map;
	if (!error_check(argc, argv))
		return (0);
	return (1);
	// game->fd = open(argv, O_RDONLY);
	// if (game->fd < 0)
	// 	return (printf("Error:\nMap file doesn't exist\n"), 0);
	// if (!read_into_map(map, game->fd))
	// 	return (0);
	// game->width = width_size(*map);
	// game->height = height_size(*map);
	// if (!map_size(*game))
	// 	return (0);
	// if (!map_validity(*map))
	// 	return (0);
	// map_copy = ft_strdup(*map);
	// if (!map_copy)
	// 	return (printf("Error:\nAllocation failed (map_copy)\n"), 0);
	// flood_fill(map_copy, player_index(*map, 'P'), game->width / 100);
	// if (!updated_map(map_copy))
	// 	return (free(map_copy), 0);
	// return (free(map_copy), 1);
}

int	main(int argc, char *argv[])
{
	t_game			game;
	char			*map;

	map = ft_strdup("");
	if (!map)
		return (printf("Error:\nAllocation failed (map)\n"), 1);
	if (!init_map(argc, argv[1], &game, &map))
		return (free(map), 1);
	// mlx_loop_hook(game.mlx, &ft_hook, &game);
	// mlx_loop(game.mlx);
	free(map);
	// return (ft_cleanup(&game, &textures), 0);
	return (0);
}
