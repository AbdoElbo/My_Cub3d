/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 20:01:50 by aelbouaz         ###   ########.fr       */
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
// we'll limit this to the limit we put ourselves, so we'll always do one read()
// and we don't have to realloc again
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map
{
	char			*str;
	struct s_map	*next;
}	t_map;

int		update_leftover(char **leftover);
char	*extract_str(char *leftover);
int		read_into_leftover(char **leftover, int fd);
char	*get_next_line(int fd);

void	free_map(t_map **map);
int		read_into_map(t_map **map, int fd);
int		error_check(int argc, char *argv);
int		check_arg(char *str);
int		init_map(int argc, char *argv, t_game *game, t_map **map);

void	cleanup(t_map **map, t_game *game);

#endif
