/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/10/03 14:24:48 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "libft/libft.h"
# include "mlx42/include/MLX42/MLX42.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>

# define BUFFER_SIZE 200
# define MAX_WIDTH 3840
# define MAX_HEIGHT 2160

typedef struct s_game
{
	mlx_t				*mlx;
	char				*str1;
	char				*str2;
	mlx_image_t			*text_image_1;
	mlx_image_t			*text_image_2;
	mlx_image_t			*i_wall;
	mlx_image_t			*i_exit;
	mlx_image_t			*i_exit_o;
	mlx_image_t			*i_passed;
	mlx_image_t			*i_wasted;
	int					status;
	int					height;
	int					width;
	int					fd;
	size_t				move_count;
}	t_game;

int	error_check(int argc, char *argv);
int	check_arg(char *str);

#endif
