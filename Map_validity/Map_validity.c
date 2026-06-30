/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:38:34 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/30 17:07:33 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

int	textures_exist(t_game *game)
{
	game->files.fd_n = open(game->files.north, O_RDONLY);
	if (game->files.fd_n < 0)
		return (printf(Y"Error:\nFailed to open North texture.\n"RESET), 0);
	game->files.fd_n_flag = 1;
	game->files.fd_w = open(game->files.west, O_RDONLY);
	if (game->files.fd_w < 0)
		return (printf(Y"Error:\nFailed to open West texture.\n"RESET), 0);
	game->files.fd_w_flag = 1;
	game->files.fd_e = open(game->files.east, O_RDONLY);
	if (game->files.fd_e < 0)
		return (printf(Y"Error:\nFailed to open East texture.\n"RESET), 0);
	game->files.fd_e_flag = 1;
	game->files.fd_s = open(game->files.south, O_RDONLY);
	if (game->files.fd_s < 0)
		return (printf(Y"Error:\nFailed to open South texture.\n"RESET), 0);
	game->files.fd_s_flag = 1;
	return (1);
}

void	set_player_direction(t_game *game)
{
	if (game->player.dir_char == 'N')
		game->player.angle = -PI / 2;
	else if (game->player.dir_char == 'S')
		game->player.angle = PI / 2;
	else if (game->player.dir_char == 'E')
		game->player.angle = 0;
	else if (game->player.dir_char == 'W')
		game->player.angle = PI;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

int	map_validity(t_game *game)
{
	int	p_exist;

	if (!textures_exist(game))
		return (0);
	p_exist = player_exists(game);
	if (p_exist > 1)
		return (printf(Y"ERROR:\nMultiple Players Found!\n"RESET), 0);
	else if (p_exist == 0)
		return (printf(Y"ERROR:\nNo Player Found!\n"RESET), false);
	set_player_direction(game);
	if (!flood_fill_outside(game))
		return (printf(Y"Error:\nMap Open to the outside world\n"RESET), 0);
	if (!check_inside(game->map))
		return (printf(Y"Error:\nUnknown char inside the map\n" RESET), 0);
	return (1);
}
