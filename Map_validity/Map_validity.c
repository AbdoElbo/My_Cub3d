/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:38:34 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/17 15:05:43 by lpieck           ###   ########.fr       */
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
	if (!flood_fill_outside(game))
		return (printf(Y"Error:\nMap Open to the outside world\n"RESET), 0);
	if (!check_inside(game->map))
		return (printf(Y"Error:\nUnknown char inside the map\n" RESET), 0);
	return (1);
}
