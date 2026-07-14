/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/14 16:15:38 by aelbouaz         ###   ########.fr       */
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

static void	delete_compass_textures(t_tex *tex)
{
	if (tex->door_tex)
		mlx_delete_texture(tex->door_tex);
	if (tex->north_tex)
		mlx_delete_texture(tex->north_tex);
	if (tex->east_tex)
		mlx_delete_texture(tex->east_tex);
	if (tex->south_tex)
		mlx_delete_texture(tex->south_tex);
	if (tex->west_tex)
		mlx_delete_texture(tex->west_tex);
}

void	cleanup(t_game *game)
{
	if (game->map)
		free_arr(game->map);
	else
		return ;
	if (game->enemy)
	{
		destroy_enemy_sprite(&game->enemy[0].sprite, game->mlx);
		free(game->enemy);
	}
	if (game->files.north)
		free(game->files.north);
	if (game->files.south)
		free(game->files.south);
	if (game->files.west)
		free(game->files.west);
	if (game->files.east)
		free(game->files.east);
	if (game->images.img)
		mlx_delete_image(game->mlx, game->images.img);
	if (game->vars.fd >= 0)
		close(game->vars.fd);
	free_files(&game->files);
	delete_compass_textures(&game->textures);
	mlx_terminate(game->mlx);
}
