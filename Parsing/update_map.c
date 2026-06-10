/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:56:06 by gekko             #+#    #+#             */
/*   Updated: 2026/06/10 15:17:25 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

static char	*make_empty(int width)
{
	char	*new;
	int		size;
	int		i;

	size = width + 2;
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = ' ';
		i++;
	}
	new[size] = '\0';
	return (new);
}

static char	*line_padding(char *str, int width)
{
	char	*new;
	int		size;
	int		i;

	new = malloc(width + 3);
	if (!new)
		return (NULL);
	new[0] = ' ';
	i = 1;
	size = ft_strlen(str);
	while (i <= width)
	{
		if (i - 1 < size)
			new[i] = str[i - 1];
		else
			new[i] = ' ';
		i++;
	}
	new[width + 1] = ' ';
	new[width + 2] = '\0';
	return (new);
}

int	update_map(t_game *game)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * (game->height + 4));
	if (!temp)
		return (0);
	temp[0] = make_empty(game->width);
	if (!temp[0])
		return (free_arr(temp), 0);
	i = 0;
	while (i < game->height + 1)
	{
		temp[i + 1] = line_padding(game->map[i + game->map_start], game->width);
		if (!temp[i + 1])
			return (free_arr(temp), 0);
		i++;
	}
	temp[game->height + 2] = make_empty(game->width);
	if (!temp[game->height + 2])
		return (free_arr(temp), 0);
	temp[game->height + 3] = NULL;
	free_arr(game->map);
	game->map = temp;
	game->map_start = 0;
	return (1);
}
