/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:14:50 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/27 14:57:31 by aelbouaz         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	if (!init_map(argc, argv[1], &game))
		return (1);
	int	i = 0;
	while (game.map[i])
		printf("%s", game.map[i++]);

	/*
		INSET CODE HERE
	*/
	return (cleanup(&game), 0);
}
