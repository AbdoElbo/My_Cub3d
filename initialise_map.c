/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:37:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/27 15:10:24 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	check_arg(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (str[len] == 'b')
	{
		len--;
		if (str[len] == 'u')
		{
			len--;
			if (str[len] == 'c')
			{
				len--;
				if (str[len] == '.')
				{
					if (!len)
						return (0);
					else
						return (1);
				}
			}
		}
	}
	return (0);
}

static int	error_check(int argc, char *argv)
{
	if (argc != 2)
	{
		printf("enter correct number of Args\n");
		printf("Example : ./cubed maps/map1.cub\n");
		return (0);
	}
	if (!check_arg(argv))
	{
		printf("Wrong File Bruh\n");
		printf("Format *.cub\n");
		return (0);
	}
	return (1);
}

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
		return (printf("Error:\nMap file doesn't exist (from read_into_map)\n"), NULL);
	map = malloc(sizeof(char *) * (num_lines + 1));
	if (!map)
		return (printf("Error:\nchar **Map Allocation failed (from read_into_map)\n"), NULL);
	i = 0;
	line = get_next_line(game->fd);
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(game->fd);
	}
	map[i] = NULL;
	return (map);
}

int	init_map(int argc, char *argv, t_game *game)
{
	if (!error_check(argc, argv))
		return (0);
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (printf("Error:\nMap file doesn't exist (from init_map)\n"), 0);
	game->map = read_into_map(game, argv);
	if (!(game->map))
		return (printf("Error:\nMap Allocation failed (from init_map)\n"), 0);
	return (1);
}
