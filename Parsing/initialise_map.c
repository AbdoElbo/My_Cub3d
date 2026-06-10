/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:37:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/10 15:12:33 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

static int	lines_counter(t_game *game)
{
	int		num_lines;
	char	*line;

	num_lines = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		free(line);
		num_lines++;
		line = get_next_line(game->fd);
	}
	close(game->fd);
	return (num_lines);
}

static char	**read_into_map(t_game *game, char *file_name)
{
	int		num_lines;
	int		i;
	char	*line;
	char	**map;

	num_lines = lines_counter(game);
	game->fd = open(file_name, O_RDONLY);
	if (game->fd < 0)
		return (printf("Error:\nMap file doesn't exist\n"), NULL);
	map = malloc(sizeof(char *) * (num_lines + 1));
	if (!map)
		return (printf("Error:\nchar **Map Allocation failed\n"), NULL);
	i = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		map[i] = line;
		if (map[i][ft_strlen(line) - 1] == '\n')
			map[i][ft_strlen(line) - 1] = '\0';
		i++;
		line = get_next_line(game->fd);
	}
	map[i] = NULL;
	return (map);
}

static void	init_vars(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->width = 0;
	game->height = 0;
	game->files.east = NULL;
	game->files.north = NULL;
	game->files.west = NULL;
	game->files.south = NULL;
	game->ceiling_color = 0;
	game->floor_color = 0;
	game->map_start = -1;
	game->img = NULL;
}

static int	get_map_size(t_game *game)
{
	char	**str;
	int		i;
	int		len;

	i = game->map_start;
	str = game->map;
	while (str[i])
	{
		if (!is_empty(str[i]))
		{
			len = ft_strlen(str[i]);
			if (game->width < len)
				game->width = len;
		}
		i++;
	}
	game->height = i - game->map_start - 1;
	if (!update_map(game))
		return (0);
	game->height += 2;
	game->width += 2;
	return (1);
}

int	init_map(int argc, char *argv, t_game *game)
{
	if (!error_check(argc, argv))
		return (0);
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (printf("Error:\nMap file doesn't exist\n"), 0);
	game->map = read_into_map(game, argv);
	if (!(game->map))
		return (0);
	init_vars(game);
	if (!check_map_order(game->map))
		return (0);
	if (!get_textures(game))
		return (0);
	if (!get_colors(game))
		return (0);
	if (!get_map_size(game))
		return (0);
	if (!game->files.north || !game->files.west
		|| !game->files.south || !game->files.east)
		return (printf("Error:\nMissing Map Textures\n"), 0);
	if (!game->ceiling_color || !game->floor_color)
		return (printf("Error:\nMissing Map Colors\n"), 0);
	return (1);
}
