/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/28 13:45:37 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// int	check_map(char **map)
// {

// }

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	cleanup(t_game *game)
{
	free_map(game->map);
	if (game->files.north)
		free(game->files.north);
	if (game->files.south)
		free(game->files.south);
	if (game->files.west)
		free(game->files.west);
	if (game->files.east)
		free(game->files.east);
	if (game->fd >= 0)
		close(game->fd);
}
