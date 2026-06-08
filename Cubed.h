/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/08 18:37:42 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "Libft/libft.h"
# include "Mlx42/include/MLX42/MLX42.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include "Macros.h"

typedef enum s_color
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	BROWN,
	CYAN,
}	t_color;

typedef struct s_files
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_files;

typedef struct s_player
{
	float	x;
	float	y;
}	t_player;

typedef struct s_game
{
	char		**map;
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
	int			map_height;
	int			map_width;
	int			map_start;
	int			fd;
}	t_game;

void	print_map(t_game *game);

#include "Parsing/Parsing.h"
#include "Map_validity/Validity.h"

#endif
