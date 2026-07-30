/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:00:44 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/28 15:25:37 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

void	draw_background_to_buf(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->framebuf, x, y, game->vars.ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(game->framebuf, x, y, game->vars.floor_color);
			x++;
		}
		y++;
	}
}

static uint32_t	sample_texture_pixel(t_ray *ray, int tex_x, int tex_y)
{
	uint8_t	*p;

	p = &ray->texture_hit.pixels[(tex_y * 128 + tex_x) * 4];
	return (*(uint32_t *)p);
}

// double step; represents how many pixels from the texture are
//  taken. the further, the less pixels.
// double tex_pos; makes sure the starting pixels are correct:
//  if close to the wall, you do not see the top part of the texture
void	draw_to_buf(t_game *game, t_ray ray, t_draw_params *dp)
{
	int			tex_x;
	double		step;
	double		tex_pos;
	int			tex_y;
	uint32_t	*dst;

	step = (double)128 / dp->line_height;
	tex_x = (int)(ray.wall_x * 128);
	tex_pos = (dp->draw_start - SCREEN_HEIGHT / 2
			+ dp->line_height / 2) * step;
	dst = (uint32_t *)game->framebuf->pixels
		+ dp->draw_start * SCREEN_WIDTH + dp->col;
	while (dp->draw_start < dp->draw_end)
	{
		tex_y = (int)tex_pos % 128;
		tex_pos += step;
		*dst = sample_texture_pixel(&ray, tex_x, tex_y);
		dst += SCREEN_WIDTH;
		dp->draw_start++;
	}
}

static t_draw_params	define_column_height(t_ray *ray, int col)
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	t_draw_params	dp;

	line_height = (int)(SCREEN_HEIGHT / (ray->distance * 1.5));
	draw_start = SCREEN_HEIGHT / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = SCREEN_HEIGHT / 2 + line_height / 2;
	if (draw_end > SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	dp.col = col;
	dp.line_height = line_height;
	dp.draw_start = draw_start;
	dp.draw_end = draw_end;
	return (dp);
}

void	render_frame(t_game *game)
{
	int				i;
	t_draw_params	dp;

	draw_background_to_buf(game);
	i = 0;
	while (i < NUM_RAYS)
	{
		dp = define_column_height(&game->rays[i], i);
		draw_to_buf(game, game->rays[i], &dp);
		i++;
	}
}
