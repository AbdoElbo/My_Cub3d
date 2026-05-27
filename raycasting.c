/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:35:15 by lpieck            #+#    #+#             */
/*   Updated: 2026/05/27 15:58:45 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "raycaster.h"

/* raycasting.c
**
** DDA (Digital Differential Analysis) raycaster for cub3D.
** One call to cast_frame() renders a full screen worth of columns.
**
** Coordinate system
**   - pos   : player position in map units (can be fractional)
**   - dir   : unit vector pointing in the direction the player faces
**   - plane : camera plane vector, perpendicular to dir,
**             length = tan(FOV/2).  With FOV ~66°, length ≈ 0.66.
**
** For each screen column x ∈ [0, SCREEN_W):
**   1. Compute the ray direction.
**   2. Run DDA to find the first wall hit.
**   3. Compute wall height and texture column.
**   4. Draw floor, ceiling, and the textured wall slice.
*/

/* ── helpers ──────────────────────────────────────────────────────────── */

/* Return the pixel colour from texture t at (tx, ty). */
static int	tex_pixel(t_tex *t, int tx, int ty)
{
	if (tx < 0)
		tx = 0;
	if (tx >= t->width)
		tx = t->width - 1;
	if (ty < 0)
		ty = 0;
	if (ty >= t->height)
		ty = t->height - 1;
	return (t->data[ty * t->width + tx]);
}

/* Write one pixel into the mlx image buffer. */
static void	put_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = g->img.addr
		+ (y * g->img.line_len + x * (g->img.bpp / 8));
	*(unsigned int *)dst = color;
}

/* Initialize step directions and initial side distances for a ray. */
static void	init_step_side_dist(t_ray *r, t_player *p)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

/* ── step 1 : ray setup ───────────────────────────────────────────────── */

static void	init_ray(t_ray *r, t_player *p, int x)
{
	r->camera_x = 2.0 * x / SCREEN_W - 1.0; /* -1 (left) … +1 (right) */
	r->dir_x = p->dir_x + p->plane_x * r->camera_x;
	r->dir_y = p->dir_y + p->plane_y * r->camera_x;

	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;

	/* delta_dist: distance the ray travels between consecutive grid lines.
	** Using fabs(1/dir) avoids a special-case when dir == 0. */
	r->delta_dist_x = (r->dir_x == 0) ? 1e30 : fabs(1.0 / r->dir_x);
	r->delta_dist_y = (r->dir_y == 0) ? 1e30 : fabs(1.0 / r->dir_y);

	/* Initial side_dist and step direction */
	init_step_side_dist(r, p);
}

/* ── step 2 : DDA loop ────────────────────────────────────────────────── */

static void	run_dda(t_ray *r, t_game *g)
{
	r->hit = 0;
	while (!r->hit)
	{
		/* Advance to the closer grid boundary */
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0; /* hit a NS wall (x-side) */
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1; /* hit an EW wall (y-side) */
		}
		/* Check map bounds defensively */
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_x >= g->map.width || r->map_y >= g->map.height)
		{
			r->hit = 1; /* treat out-of-bounds as wall */
			break ;
		}
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

/* ── step 3 : wall geometry and texture column ────────────────────────── */

static void	calc_wall(t_ray *r, t_player *p)
{
	/* Perpendicular distance (avoids fisheye distortion) */
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;

	r->line_height = (int)(SCREEN_H / r->perp_wall_dist);
	r->draw_start = SCREEN_H / 2 - r->line_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = SCREEN_H / 2 + r->line_height / 2;
	if (r->draw_end >= SCREEN_H)
		r->draw_end = SCREEN_H - 1;

	/* Exact hit position on the wall face (0..1) */
	if (r->side == 0)
		r->wall_x = p->pos_y + r->perp_wall_dist * r->dir_y;
	else
		r->wall_x = p->pos_x + r->perp_wall_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
}

/* Pick the correct texture based on which face was hit. */
static t_tex	*pick_texture(t_ray *r, t_game *g)
{
	if (r->side == 0)
	{
		if (r->step_x > 0)
			return (&g->tex[TEX_E]);
		return (&g->tex[TEX_W]);
	}
	else
	{
		if (r->step_y > 0)
			return (&g->tex[TEX_S]);
		return (&g->tex[TEX_N]);
	}
}

/* ── step 4 : draw one screen column ─────────────────────────────────── */

static void	draw_column(t_game *g, t_ray *r, int x)
{
	t_tex	*tex;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	tex = pick_texture(r, g);
	r->tex_x = (int)(r->wall_x * tex->width);
	/* Flip texture x on east/south-facing walls to avoid mirroring */
	if ((r->side == 0 && r->dir_x < 0)
		|| (r->side == 1 && r->dir_y > 0))
		r->tex_x = tex->width - r->tex_x - 1;

	step = (double)tex->height / r->line_height;
	/* Start texel: offset if draw_start was clamped */
	tex_pos = (r->draw_start - SCREEN_H / 2.0 + r->line_height / 2.0) * step;

	/* Ceiling */
	y = 0;
	while (y < r->draw_start)
	{
		put_pixel(g, x, y, C);
		y++;
	}

	/* Textured wall slice */
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1); /* fast modulo for pow2 */
		tex_pos += step;
		color = tex_pixel(tex, r->tex_x, tex_y);
		/* Darken EW walls for a shading effect */
		if (r->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(g, x, y, color);
		y++;
	}

	/* Floor */
	y = r->draw_end + 1;
	while (y < SCREEN_H)
	{
		put_pixel(g, x, y, g->floor_color);
		y++;
	}
}

/* ── public entry point ───────────────────────────────────────────────── */

/*
** cast_frame — render one full frame into g->img.
** Call this once per frame (in your game loop), then mlx_put_image_to_window.
*/
void	cast_frame(t_game *g)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(&r, &g->player, x);
		run_dda(&r, g);
		calc_wall(&r, &g->player);
		draw_column(g, &r, x);
		x++;
	}
}