/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/09 13:12:37 by lpieck           ###   ########.fr       */
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
	long long	current;
	long long	delta;
	long long	last_move;
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

typedef struct s_game
{
	char		**map;
	mlx_image_t	*mm_img;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			multiplier;
	t_files		files;
	t_ray		rays[NUM_RAYS];
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			status;
	int			height;
	int			width;
	int			map_start;
	int			fd;
	mlx_image_t	*framebuf;
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
