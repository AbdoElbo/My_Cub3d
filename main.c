/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 19:19:54 by aelbouaz         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	char	**map;

	map = NULL;
	if (!init_map(argc, argv[1], &game, map))
		return (1);
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	// mlx_loop_hook(game.mlx, &ft_hook, &game);
	// mlx_loop(game.mlx);
	free_map(map);
	close(game.fd);
	// return (ft_cleanup(&game, &textures), 0);
	return (0);
}
