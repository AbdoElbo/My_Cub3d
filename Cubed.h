/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/23 20:37:35 by gekko            ###   ########.fr       */
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
	float		dir_x;
	float		dir_y;
	float		speed;
	float		dir_float;
	char		dir_char;
}	t_player;

typedef struct s_game
{
	char		**map;
	mlx_image_t	*mm_img;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			multiplier;
	t_files		files;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			status;
	int			height;
	int			width;
	int			map_start;
	int			fd;
}	t_game;

void	print_map(t_game *game);
void	print_2array(char **arr);

#endif
