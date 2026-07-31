/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:45:28 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/31 13:21:07 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

int	allocate_text(t_game *game)
{
	game->collect_str = NULL;
	game->collect_str = ft_calloc(40, sizeof(char));
	if (!game->collect_str)
		return (printf("Error:\ngame->collect_str allocation failed\n"), 0);
	game->player_hp_str = NULL;
	game->player_hp_str = ft_calloc(40, sizeof(char));
	if (!game->player_hp_str)
		return (printf("Error:\ngame->player_hp_str allocation failed\n"), 0);
	ft_strlcpy(game->collect_str, "Collectibles obtained: ", 25);
	ft_strlcpy(game->player_hp_str, "Player's HP: ", 15);
	game->images.collect_text = NULL;
	game->images.player_hp_txt = NULL;
	return (1);
}

int	load_map_and_components(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Our Awesome Game", 1);
	if (!game->mlx)
		return (printf("Error:\nMlx initialization failed\n"), 0);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->framebuf = mlx_new_image(game->mlx, MAX_WIDTH, MAX_HEIGHT);
	mlx_image_to_window(game->mlx, game->framebuf, 0, 0);
	game->images.mm_img = mlx_new_image(game->mlx, MINIMAP_PX, MINIMAP_PX);
	if (!game->images.mm_img)
		return (printf("Error:\nMlx img_mm creation failed\n"), 0);
	if (mlx_image_to_window(game->mlx, game->images.mm_img, 0, 0))
		return (printf("Error:\nMlx img_mm image_to_window failed\n"), 0);
	if (!load_compass_tex(game))
		return (0);
	if (!load_gun_tex(game))
		return (0);
	if (!allocate_text(game))
		return (0);
	return (1);
}

void	order_enemy_array(t_enemy *enemies, int enemy_count)
{
	t_enemy	temp;
	int		i;
	int		j;

	i = 0;
	while (i < enemy_count)
	{
		j = i + 1;
		while (j < enemy_count)
		{
			if (enemies[j].dst_from_player > enemies[i].dst_from_player)
			{
				temp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = temp;
			}
			j++;
		}
		i++;
	}
}

// 0 for vertical wall, 1 for horizontal wall
double	hit_wall_x(t_dda *dda, t_ray *ray, t_game *game)
{
	if (dda->side == 0)
	{
		dda->raw_dist = dda->side_dist_x - dda->delta_dist_x;
		dda->hit_y = game->player.y + dda->raw_dist * ray->dir_y;
		return (dda->hit_y - floor(dda->hit_y));
	}
	else
	{
		dda->raw_dist = dda->side_dist_y - dda->delta_dist_y;
		dda->hit_x = game->player.x + dda->raw_dist * ray->dir_x;
		return (dda->hit_x - floor(dda->hit_x));
	}
}

// calculate the lenght of the ray to cross exactly one
// tile in both x and y direction if delta_dist_y < delta_dist_x,
// it means the ray is going going up/down sharper
void	init_delta_dist(t_dda *dda, t_ray *ray)
{
	if (ray->dir_x == 0)
		dda->delta_dist_x = INFINITY;
	else
		dda->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		dda->delta_dist_y = INFINITY;
	else
		dda->delta_dist_y = fabs(1 / ray->dir_y);
}
