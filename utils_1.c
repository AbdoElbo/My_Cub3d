/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/04 14:15:10 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
	free_arr(game->map);
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
