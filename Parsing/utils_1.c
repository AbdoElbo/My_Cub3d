/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/09 15:08:19 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

char **copy_map(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_arr(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while(str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int	arr_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	cleanup(t_game *game)
{
	if (game->map)
		free_arr(game->map);
	else
		return ;
	if (game->files.north)
		free(game->files.north);
	if (game->files.south)
		free(game->files.south);
	if (game->files.west)
		free(game->files.west);
	if (game->files.east)
		free(game->files.east);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->fd >= 0)
		close(game->fd);
}
