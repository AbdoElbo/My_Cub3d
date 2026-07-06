/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:00:44 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/06 14:38:55 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

void	 draw_background_to_buf(t_game *game)
{
	int i;
	uint32_t *pixels;

	pixels = (uint32_t *)game->framebuf->pixels;
	i = 0;
	while (i < (SCREEN_HEIGHT / 2) * SCREEN_WIDTH)
	{
		pixels[i] = game->ceiling_color;
		i++;
	}
	while (i < SCREEN_HEIGHT * SCREEN_WIDTH)
	{
		pixels[i] = game->floor_color;
		i++;
	}
}

static uint32_t	 sample_texture_pixel(t_game *game, int tex_x, int tex_y)
{
	uint8_t *p;

	p = &game->rays->texture->pixels[(tex_y * 128 + tex_x) * 4];
	return (*(uint32_t *)p);
}

void	 draw_to_buf(t_game *game, t_ray *ray, t_draw_params *dp)
{
	int			tex_x;
	double		step; // how many pixels from the texture are taken. the further, the less pixels
	double		tex_pos; // makes sure the starting pixels are correct: if close to the wall, you do not see the top part of the texture
	int			tex_y;
	uint32_t	*dst;

	step = (double)128 / dp->line_height;
	tex_x = (int)(ray->wall_x * 128);
	tex_pos = (dp->draw_start - SCREEN_HEIGHT / 2 + dp->line_height / 2) * step;
	dst = (uint32_t *)game->framebuf->pixels + dp->draw_start * SCREEN_WIDTH + dp->col;
	while (dp->draw_start < dp->draw_end)
	{
		tex_y = (int)tex_pos % 128;
		tex_pos += step;
		*dst = sample_texture_pixel(game, tex_x, tex_y);
		dst += SCREEN_WIDTH;
		dp->draw_start++;
	}
}

t_draw_params	 define_column_height(t_ray *ray, int col)
{
	// shoot_ray();
	// texture resolution currently is 128 x 128
	// game->ray.distance = 2.0;
	// game->rays.angle = 0.0;
	// ray->wall_x = 0.5;

	int line_height;
	int draw_start;
	int draw_end;
	t_draw_params dp;

	line_height = (int)(SCREEN_HEIGHT / ray->distance);
	draw_start = SCREEN_HEIGHT / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = SCREEN_HEIGHT / 2 + line_height / 2;
	if (draw_end > SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1; //test what happens without - 1
	dp.col = col;
	dp.line_height = line_height;
	dp.draw_start = draw_start;
	dp.draw_end = draw_end;
	return (dp);
}

void	 render_frame(t_game *game)
{
	int i;
	t_draw_params dp;

	draw_background_to_buf(game);
	i = 0;
	while (i < NUM_RAYS) // i <
	{
		printf("ray distance: %f\n", game->rays[i].distance);
		printf("ray wall_x: %f\n", game->rays[i].wall_x);
		dp = define_column_height(&game->rays[i], i);
		draw_to_buf(game, &game->rays[i], &dp);
		i++;
	}
	// render_buf_to_screen(game);
}
	