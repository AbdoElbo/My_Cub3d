/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:16:42 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/19 17:53:39 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

static long long	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	move_forwards(t_game *game)
{
	char	temp;
	int		x;
	int		y;

	game->player.current = get_time_in_ms();
	if (game->player.current - game->player.last_move < game->player.speed)
		return ;
	x = game->player.x;
	y = game->player.y;
	temp = game->map[x][y];
	if (game->map[x - 1][y] == '1')
		return ;
	game->player.last_move = game->player.current;
	game->map[x][y] = game->map[x - 1][y];
	game->map[x - 1][y] = temp;
	game->player.x = game->player.x - 1;
}

void	move_backwards(t_game *game)
{
	char	temp;
	int		x;
	int		y;

	game->player.current = get_time_in_ms();
	if (game->player.current - game->player.last_move < game->player.speed)
		return ;
	x = game->player.x;
	y = game->player.y;
	temp = game->map[x][y];
	if (game->map[x + 1][y] == '1')
		return ;
	game->player.last_move = game->player.current;
	game->map[x][y] = game->map[x + 1][y];
	game->map[x + 1][y] = temp;
	game->player.x = game->player.x + 1;
}

void	move_right(t_game *game)
{
	char	temp;
	int		x;
	int		y;

	game->player.current = get_time_in_ms();
	if (game->player.current - game->player.last_move < game->player.speed)
		return ;
	x = game->player.x;
	y = game->player.y;
	temp = game->map[x][y];
	if (game->map[x][y + 1] == '1')
		return ;
	game->player.last_move = game->player.current;
	game->map[x][y] = game->map[x][y + 1];
	game->map[x][y + 1] = temp;
	game->player.y = game->player.y + 1;
}

void	move_left(t_game *game)
{
	char	temp;
	int		x;
	int		y;

	game->player.current = get_time_in_ms();
	if (game->player.current - game->player.last_move < game->player.speed)
		return ;
	x = game->player.x;
	y = game->player.y;
	temp = game->map[x][y];
	if (game->map[x][y - 1] == '1')
		return ;
	game->player.last_move = game->player.current;
	game->map[x][y] = game->map[x][y - 1];
	game->map[x][y - 1] = temp;
	game->player.y = game->player.y - 1;
}
