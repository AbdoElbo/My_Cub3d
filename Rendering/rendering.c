/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:00:44 by lpieck            #+#    #+#             */
/*   Updated: 2026/06/18 14:58:43 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"


void draw_background_to_buf(t_game *game)
{
	int i;
	uint32_t *pixels;

	pixels = (uint32_t *)game->framebuf->pixels;
	i = 0;
	while (i < (MAX_HEIGHT / 2) * MAX_WIDTH)
	{
		pixels[i] = game->ceiling_color;
		i++;
	}
	while (i < MAX_HEIGHT * MAX_WIDTH)
	{
		pixels[i] = game->floor_color;
		i++;
	}
}

void draw_column_to_buf(t_game *game, int col)
{
	// shoot_ray();
	// texture resolution currently is 1024 x 1024
	game->ray.distance = 2.0;
	game->ray.angle = 0.0;
	game->ray.wall_x = 0.5;

	int line_height;
	int draw_start;
	int draw_end;
	int tex_x;

	line_height = (int)(MAX_HEIGHT / game->ray.distance);
	draw_start = MAX_HEIGHT / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = MAX_HEIGHT / 2 + line_height / 2;
	if (draw_end > MAX_HEIGHT)
		draw_end = MAX_HEIGHT - 1; //test what happens without - 1
	tex_x = (int)(game->ray.wall_x * 1024);


	double step    = (double)1024 / line_height;
	double tex_pos = (draw_start - MAX_HEIGHT / 2 + line_height / 2) * step;

	uint32_t *pixels = (uint32_t *)game->framebuf->pixels;

	for (int y = draw_start; y < draw_end; y++)
	{
		int tex_y = (int)tex_pos % 1024;
		tex_pos += step;

		uint8_t *p    = &game->ray.texture->pixels[(tex_y * 1024 + tex_x) * 4];
		// uint32_t color = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0]; this is an option as well, dont understand the difference yet
		uint32_t color = *(uint32_t *)p;
		pixels[y * MAX_WIDTH + col] = color;
	}
}

void render_frame(t_game *game)
{
	int i;

	draw_background_to_buf(game);
	i = 0;
	while (i < MAX_WIDTH) // i <
	{
		draw_column_to_buf(game, i);
		i++;
	}
	// render_buf_to_screen(game);
}
