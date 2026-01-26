/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:37:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 19:20:30 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
}

void	read_into_map(char **map, int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		map[i] = tmp;
		i++;
	}
	map[i] = NULL;
}

int	init_map(int argc, char *argv, t_game *game, char **map)
{
	printf("HELLO");
	if (!error_check(argc, argv))
		return (0);
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (printf("Error:\nMap file doesn't exist\n"), 0);
	read_into_map(map, game->fd);
	return (1);
}
