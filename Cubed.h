/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/18 14:38:13 by aelbouaz         ###   ########.fr       */
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
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	speed;
	char	direction;
}	t_player;

typedef struct s_game
{
	char		**map;
	char		**mini;
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
