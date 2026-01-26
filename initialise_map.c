/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:37:49 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 19:58:06 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	add_back(t_map **map, t_map *new)
{
	t_map	*cur;

	if (!*map)
	{
		*map = new;
		return ;
	}
	cur = *map;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_map	*create_node(char *line)
{
	t_map	*new_node;

	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (0);
	new_node->str = ft_strdup(line);
	if (!new_node->str)
		return (free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

void	free_map(t_map **map)
{
	t_map	*temp;

	if (!map || !*map)
		return ;
	temp = *map;
	while (*map)
	{
		temp = (*map)->next;
		free((*map)->str);
		free((*map));
		(*map) = temp;
	}
	(*map) = NULL;
}

int	read_into_map(t_map **map, int fd)
{
	char	*line;
	t_map	*temp;

	line = get_next_line(fd);
	while (line)
	{
		temp = create_node(line);
		if (!temp)
			return (free_map(map), 0);
		add_back(map, temp);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	init_map(int argc, char *argv, t_game *game, t_map **map)
{
	if (!error_check(argc, argv))
		return (0);
	game->fd = open(argv, O_RDONLY);
	if (game->fd < 0)
		return (printf("Error:\nMap file doesn't exist\n"), 0);
	read_into_map(map, game->fd);
	return (1);
}
