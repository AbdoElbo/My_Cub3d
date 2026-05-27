/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:59:17 by lpieck            #+#    #+#             */
/*   Updated: 2026/05/27 14:01:30 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>

# include <math.h>
 
# define SCREEN_W	1280
# define SCREEN_H	720
# define FOV		0.66  /* half the width of the camera plane (66° total FOV) */
# define MOVE_SPD	0.05
# define ROT_SPD	0.03
 
/* Represents one ray's result after DDA */
typedef struct s_ray
{
	double	camera_x;    /* x in camera space: [-1, 1] */
	double	dir_x;
	double	dir_y;
	int		map_x;       /* current map cell */
	int		map_y;
	double	side_dist_x; /* distance to next x/y grid line */
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;         /* 1 = wall hit */
	int		side;        /* 0 = NS wall, 1 = EW wall */
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;      /* exact hit position on wall (0..1), for texture */
	int		tex_x;       /* texture column */
}	t_ray;
 
/* Player state */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;    /* camera plane, perpendicular to dir */
	double	plane_y;
}	t_player;
 
/* Texture (loaded XPM/PNG data) */
typedef struct s_tex
{
	int		*data;      /* mlx_get_data_addr pixel array */
	int		width;
	int		height;
}	t_tex;
 
/* Texture indices */
# define TEX_N 0
# define TEX_S 1
# define TEX_E 2
# define TEX_W 3
 
/* Forward-declare your game struct here so you can pass it around */
/* (fill the rest of it in your cub3d.h) */
typedef struct s_game t_game;
 
/* ---- raycasting.c prototypes ---- */
void	cast_frame(t_game *g);


# endif