/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/14 13:16:47 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "Libraries/Libft/libft.h"
# include "Libraries/Mlx42/include/MLX42/MLX42.h"
# include "Libraries/Macros.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include "Parsing/Parsing.h"
# include "Map_validity/Validity.h"
# include "Plane/Plane.h"
# include "Game_Dev/Game_Dev.h"

# define PI 3.14159265358979323846
# include "Rendering/Rendering.h"
# include "Enemy/enemy.h"

typedef enum e_weapons
{
	SWORD,
	OTHER,
}	t_weapons;

typedef struct s_files
{
	char	*north;
	int		fd_n;
	int		fd_n_flag;
	char	*south;
	int		fd_s;
	int		fd_s_flag;
	char	*west;
	int		fd_w;
	int		fd_w_flag;
	char	*east;
	int		fd_e;
	int		fd_e_flag;
}	t_files;

typedef struct s_player
{
	float		delta_x;
	float		delta_y;
	float		previous_x;
	float		previous_y;
	float		x;
	float		y;
	float		angle;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		speed;
	float		dir_float;
	char		dir_char;
}	t_player;

typedef struct s_ray
{
	double	distance;
	double	angle;
	double	wall_x; // between 0.0 and 1.0
	double	dir_x;
	double	dir_y;
	int	side; // 0 for vertical wall, 1 for horizontal wall
	mlx_texture_t	texture_hit;
}	t_ray;

typedef struct s_tex
{
	mlx_texture_t		*sword_tex_0;
	mlx_texture_t		*sword_tex_1;
	mlx_texture_t		*sword_tex_2;
	mlx_texture_t		*sword_tex_3;
	mlx_texture_t		*sword_tex_4;
	mlx_texture_t		*other_tex_0;
	mlx_texture_t		*other_tex_1;
	mlx_texture_t		*other_tex_2;
	mlx_texture_t		*other_tex_3;
	mlx_texture_t		*other_tex_4;
}	t_tex;

typedef struct s_img
{
	mlx_image_t		*sword_img_0;
	mlx_image_t		*sword_img_1;
	mlx_image_t		*sword_img_2;
	mlx_image_t		*sword_img_3;
	mlx_image_t		*sword_img_4;
	mlx_image_t		*other_img_0;
	mlx_image_t		*other_img_1;
	mlx_image_t		*other_img_2;
	mlx_image_t		*other_img_3;
	mlx_image_t		*other_img_4;
}	t_img;

typedef enum e_movement
{
	FREE,
	BUSY,
}	t_movement;

typedef enum e_frame
{
	IDLE,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
}	t_frame;

typedef struct s_game
{
	char		**map;
	mlx_image_t	*mm_img;
	mlx_image_t	*img;
	mlx_image_t	*framebuf;
	t_player	player;
	mlx_t		*mlx;
	int			multiplier;
	t_files		files;
	t_ray		rays[NUM_RAYS];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	double		mouse_x;
	double		mouse_y;
	int			status;
	int			height;
	int			width;
	int			map_start;
	int			fd;
	t_img		images;
	t_tex		textures;
	t_weapons	weapon;
	t_movement	movement;
	t_frame		frame;
	long long	frame_start;
	bool		mouse_was_down;
	double		zbuffer[MAX_WIDTH];
	t_enemy		enemy;
	mlx_texture_t	*texture_east;
	mlx_texture_t	*texture_west;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_north;
	// mlx_texture_t	*texture_door;
}	t_game;

void	print_map(t_game *game);

#endif
