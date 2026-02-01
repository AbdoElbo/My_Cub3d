/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/28 19:35:47 by aelbouaz         ###   ########.fr       */
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

# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"
# define R "\033[1;31m"
# define RESET "\033[0m"

typedef struct s_files
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_files;

typedef struct s_game
{
	char		**map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_files		files;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			status;
	int			height;
	int			width;
	int			fd;
}	t_game;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

int		update_leftover(char **leftover);
char	*extract_str(char *leftover);
int		read_into_leftover(char **leftover, int fd);
char	*get_next_line(int fd);

int		init_map(int argc, char *argv, t_game *game);
int		load_map_and_components(t_game *game);
void	init_vars(t_game *game);
int		get_textures(t_game *game);
int		get_colors(t_game *game);

void	free_map(char **map);
void	cleanup(t_game *game);

#endif
