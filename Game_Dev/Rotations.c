/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 16:54:14 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/13 19:30:27 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game_Dev.h"

void	ft_mouse_mvm(double x, double y, void *param)
{
	t_game	*game;
	int32_t	current_x;
	int32_t	current_y;
	int		dx;
	float	rot_speed;

	(void)y;
	(void)x;
	current_x = 0;
	current_y = 0;
	game = (t_game *)param;
	rot_speed = 0.001f;
	mlx_get_mouse_pos(game->mlx, &current_x, &current_y);
	dx = current_x - game->mouse_x;
	mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	game->player.angle += dx * rot_speed;
}

void	rotate_player(t_game *game)
{
	float	rot_speed;

	rot_speed = 0.05f;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player.angle -= rot_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player.angle += rot_speed;
	game->player.dir_x = cos(game->player.angle);
	game->player.dir_y = sin(game->player.angle);
}

void	draw_line(t_game *game, uint32_t color)
{
	int		i;
	int		j;
	double	x;
	double	y;
	double	distance;

	x = 0;
	y = 0;
	distance = 0;
	i = MINIMAP_PX / 2;
	j = MINIMAP_PX / 2;
	while (distance < MINIMAP_PX)
	{
		x = i + game->player.dir_x * distance;
		y = j + game->player.dir_y * distance;
		if (x > 0 && x < MINIMAP_PX && y > 0 && y < MINIMAP_PX)
			mlx_put_pixel(game->mm_img, x, y, color);
		distance++;
	}
}
