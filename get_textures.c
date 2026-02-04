/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:55:37 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/04 14:03:46 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_north_location(t_game *game, int i, int j)
{
	char	*str;
	int		k;

	j += 2;
	str = game->map[i];
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (printf("Error:\nNorth texture not found!\n"), 0);
	if (game->files.north)
		return (printf("Error:\nDuplicated North texture\n"), 0);
	k = j;
	while (str[k] && str[k] != '\n')
		k++;
	game->files.north = ft_substr(str, j, k - j);
	if (!game->files.north)
		return (printf("Error:\nfiles.north allocation failed\n"), 0);
	return (1);
}

static int	get_south_location(t_game *game, int i, int j)
{
	char	*str;
	int		k;

	j += 2;
	str = game->map[i];
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (printf("Error:\nSouth texture not found!\n"), 0);
	if (game->files.south)
		return (printf("Error:\nDuplicated South texture\n"), 0);
	k = j;
	while (str[k] && str[k] != '\n')
		k++;
	game->files.south = ft_substr(str, j, k - j);
	if (!game->files.south)
		return (printf("Error:\nfiles.South allocation failed\n"), 0);
	return (1);
}

static int	get_west_location(t_game *game, int i, int j)
{
	char	*str;
	int		k;

	j += 2;
	str = game->map[i];
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (printf("Error:\nWest texture not found!\n"), 0);
	if (game->files.west)
		return (printf("Error:\nDuplicated West texture\n"), 0);
	k = j;
	while (str[k] && str[k] != '\n')
		k++;
	game->files.west = ft_substr(str, j, k - j);
	if (!game->files.west)
		return (printf("Error:\nfiles.west allocation failed\n"), 0);
	return (1);
}

static int	get_east_location(t_game *game, int i, int j)
{
	char	*str;
	int		k;

	j += 2;
	str = game->map[i];
	while (str[j] && ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (printf("Error:\nEast texture not found!\n"), 0);
	if (game->files.east)
		return (printf("Error:\nDuplicated East texture\n"), 0);
	k = j;
	while (str[k] && str[k] != '\n')
		k++;
	game->files.east = ft_substr(str, j, k - j);
	if (!game->files.east)
		return (printf("Error:\nfiles.east allocation failed\n"), 0);
	return (1);
}

int	get_textures(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] == '\t' || game->map[i][j] == ' ')
			j++;
		if (ft_strncmp(&game->map[i][j], "NO", 2) == 0
				&& !get_north_location(game, i, j))
			return (0);
		else if (ft_strncmp(&game->map[i][j], "SO", 2) == 0
				&& !get_south_location(game, i, j))
			return (0);
		else if (ft_strncmp(&game->map[i][j], "WE", 2) == 0
				&& !get_west_location(game, i, j))
			return (0);
		else if (ft_strncmp(&game->map[i][j], "EA", 2) == 0
				&& !get_east_location(game, i, j))
			return (0);
		i++;
	}
	return (1);
}
