/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:16:42 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/24 17:47:50 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

// static int	is_wall(t_game *game, float x, float y)
// {
// 	int map_col;
// 	int map_row;

// 	map_col = (int)x;
// 	map_row = (int)y;
// 	if (map_row < 0 || map_row >= game->height
// 		|| map_col < 0 || map_col >= game->width)
// 		return (1);
// 	if (!game->map[map_row])
// 		return (1);
// 	if (map_col >= (int)ft_strlen(game->map[map_row]))
// 		return (1);
// 	return (game->map[map_row][map_col] == '1');
// }

void	move_player(t_game *game)
{
	int		nx;
	int		ny;
	float	speed;

	speed = 0.1f;
	nx = game->player.x;
	ny = game->player.y;
	printf("x: %f  y: %f\n", game->player.x, game->player.y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player.y -= speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player.y += speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.x  += speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.x  -= speed;
	// if (!is_wall(game, nx, ny))
	// {
	// game->player.x = nx;
	// game->player.y = ny;
	// }/
}
