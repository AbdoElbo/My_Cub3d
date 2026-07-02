/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:16:42 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/02 18:42:04 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static int	is_wall(t_game *game, float x, float y)
{
	int		map_col;
	int		map_row;
	char	c;

	map_col = (int)floorf(x);
	map_row = (int)floorf(y);
	if (map_row < 0 || map_row >= game->height
		|| map_col < 0 || map_col >= game->width)
		return (1);
	if (!game->map[map_row])
		return (1);
	if (map_col >= (int)ft_strlen(game->map[map_row]))
		return (1);
	c = game->map[map_row][map_col];
	if (c == '1' || c == ' ' || c == '.')
		return (1);
	return (0);
}

static int	hits_wall(t_game *game, float x, float y)
{
	float	m;

	m = 0.09f;
	return (is_wall(game, x + m, y + m)
		|| is_wall(game, x - m, y + m)
		|| is_wall(game, x + m, y - m)
		|| is_wall(game, x - m, y - m));
}

static void	move_dir(t_game *game, float *nx, float *ny, int dir)
{
	float	speed = 0.05f;

	if (dir == 0)
	{
		*nx += game->player.dir_x * speed;
		*ny += game->player.dir_y * speed;
	}
	else if (dir == 1)
	{
		*nx -= game->player.dir_x * speed;
		*ny -= game->player.dir_y * speed;
	}
	else if (dir == 2)
	{
		*nx -= game->player.dir_y * speed;
		*ny += game->player.dir_x * speed;
	}
	else if (dir == 3)
	{
		*nx += game->player.dir_y * speed;
		*ny -= game->player.dir_x * speed;
	}
}

void	move_player(t_game *game)
{
	float	nx;
	float	ny;
	float	speed;

	speed = 0.05f;
	nx = game->player.x;
	ny = game->player.y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_dir(game, &nx, &ny, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_dir(game, &nx, &ny, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_dir(game, &nx, &ny, 2);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_dir(game, &nx, &ny, 3);
	if (!hits_wall(game, nx, game->player.y))
		game->player.x = nx;
	if (!hits_wall(game, game->player.x, ny))
		game->player.y = ny;
}
