/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/10 15:08:58 by aelbouaz         ###   ########.fr       */
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

typedef struct s_files
{
	char	*north;
	int		fd_n;
	char	*south;
	int		fd_s;
	char	*west;
	int		fd_w;
	char	*east;
	int		fd_e;
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

#endif
