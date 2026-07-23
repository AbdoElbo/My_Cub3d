/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:37:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/23 17:51:53 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

static int	lines_counter(t_game *game)
{
	int		num_lines;
	char	*line;

	num_lines = 0;
	line = get_next_line(game->vars.fd);
	while (line)
	{
		free(line);
		num_lines++;
		line = get_next_line(game->vars.fd);
	}
	close(game->vars.fd);
	return (num_lines);
}

static char	**read_into_map(t_game *game, char *file_name)
{
	int		num_lines;
	int		i;
	char	*line;
	char	**map;

	num_lines = lines_counter(game);
	game->vars.fd = open(file_name, O_RDONLY);
	if (game->vars.fd < 0)
		return (printf("Error:\nMap file doesn't exist\n"), NULL);
	map = malloc(sizeof(char *) * (num_lines + 1));
	if (!map)
		return (printf("Error:\nchar **Map Allocation failed\n"), NULL);
	i = 0;
	line = get_next_line(game->vars.fd);
	while (line)
	{
		map[i] = line;
		if (map[i][ft_strlen(line) - 1] == '\n')
			map[i][ft_strlen(line) - 1] = '\0';
		i++;
		line = get_next_line(game->vars.fd);
	}
	map[i] = NULL;
	return (map);
}

static void	init_vars(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.health = PLAYER_HEALTH;
	game->enemy = NULL;
	game->doors = NULL;
	game->mlx = NULL;
	game->framebuf = NULL;
	game->vars.width = 0;
	game->vars.height = 0;
	game->files.east = NULL;
	game->files.north = NULL;
	game->files.west = NULL;
	game->files.south = NULL;
	game->vars.ceiling_color = 0;
	game->vars.floor_color = 0;
	game->vars.map_start = -1;
	game->vars.easter_egg = 0;
	game->files.fd_e_flag = 0;
	game->files.fd_n_flag = 0;
	game->files.fd_w_flag = 0;
	game->files.fd_s_flag = 0;
	game->vars.mouse_x = SCREEN_WIDTH / 2;
	game->vars.mouse_y = SCREEN_HEIGHT / 2;
	game->movement = FREE;
	game->weapon = SWORD;
	game->vars.mouse_was_down = false;
	game->vars.fd = -1;
}

static int	get_map_size(t_game *game)
{
	char	**str;
	int		i;
	int		len;

	i = game->vars.map_start;
	str = game->map;
	while (str[i])
	{
		if (!is_empty(str[i]))
		{
			len = ft_strlen(str[i]);
			if (game->vars.width < len)
				game->vars.width = len;
		}
		i++;
	}
	game->vars.height = i - game->vars.map_start - 1;
	if (!update_map(game))
		return (0);
	game->vars.height += 2;
	game->vars.width += 2;
	return (1);
}

static void	set_easter(t_game *game, char *str)
{
	if (!ft_strncmp(str, "goofy", 6))
		game->vars.easter_egg = 1;
}

int	init_map(int argc, char **argv, t_game *game)
{
	if (!error_check(argc, argv[1]))
		return (0);
	game->vars.fd = open(argv[1], O_RDONLY);
	if (game->vars.fd < 0)
		return (printf("Error:\nMap file doesn't exist\n"), 0);
	game->map = read_into_map(game, argv[1]);
	if (!(game->map))
		return (0);
	init_vars(game);
	if (argc == 3)
		set_easter(game, argv[2]);
	if (!check_map_order(game->map))
		return (0);
	if (!get_textures(game) || !get_colors(game))
		return (0);
	if (!get_map_size(game))
		return (0);
	if (!game->files.north || !game->files.west
		|| !game->files.south || !game->files.east)
		return (printf("Error:\nMissing Map Textures\n"), 0);
	if (!game->vars.ceiling_color || !game->vars.floor_color)
		return (printf("Error:\nMissing Map Colors\n"), 0);
	return (1);
}
