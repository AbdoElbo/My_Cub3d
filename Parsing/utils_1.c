/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/23 18:14:16 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
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

static void	free_files(t_files *files)
{
	if (files->north)
		free(files->north);
	if (files->south)
		free(files->south);
	if (files->west)
		free(files->west);
	if (files->east)
		free(files->east);
	if (files->fd_n_flag)
		close(files->fd_n);
	if (files->fd_e_flag)
		close(files->fd_e);
	if (files->fd_s_flag)
		close(files->fd_s);
	if (files->fd_w_flag)
		close(files->fd_w);
}

static void	delete_textures(t_game *game)
{
	if (game->textures.north_tex)
		mlx_delete_texture(game->textures.north_tex);
	if (game->textures.east_tex)
		mlx_delete_texture(game->textures.east_tex);
	if (game->textures.south_tex)
		mlx_delete_texture(game->textures.south_tex);
	if (game->textures.west_tex)
		mlx_delete_texture(game->textures.west_tex);
	if (game->textures.door_tex)
		mlx_delete_texture(game->textures.door_tex);
	if (game->textures.collectible_tex)
		mlx_delete_texture(game->textures.collectible_tex);
}

void	cleanup(t_game *game)
{
	if (game->map)
		free_arr(game->map);
	else
		return ;
	if (game->doors)
		free(game->doors);
	if (game->enemy && game->vars.enemy_count > 0)
	{
		destroy_enemy_sprite(&game->enemy[0].sprite, game->mlx);
		free(game->enemy);
	}
	if (game->vars.fd >= 0)
		close(game->vars.fd);
	free_files(&game->files);
	delete_textures(game);
	if (game->collect_str)
		free(game->collect_str);
	if (game->player_hp_str)
		free(game->player_hp_str);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
