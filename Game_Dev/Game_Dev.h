/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game_Dev.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:17:07 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/17 16:35:08 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEV_H
# define GAME_DEV_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;
typedef struct s_ray	t_ray ;

typedef struct s_door
{
	int		x;
	int		y;
	bool	open;
}	t_door;

typedef struct s_collect
{
	float		x;
	float		y;
	bool		available;
}	t_collect;


void		cast_rays(t_game *game);
void		move_player(t_game *game);
void		ft_mouse_mvm(double x, double y, void *param);
void		rotate_player(t_game *game);
void		draw_line(t_game *game, t_ray *ray, uint32_t color);
void		gun_dev(t_game *game);

int			load_images(t_game *game, char *path
				, mlx_texture_t **tex, mlx_image_t **img);
int			load_sword_tex(t_game *game);
int			load_shotgun_tex(t_game *game);
int			load_fish_tex(t_game *game);
int			load_nokia_tex(t_game *game);
int			load_compass_tex(t_game *game);
long long	get_time_in_ms(void);

void		sword_attack(t_game *game);
void		shotgun_attack(t_game *game);

int			is_wall(t_game *game, float x, float y);
int			hits_wall(t_game *game, float x, float y);

int			init_doors(t_game *game);
int			init_collectibles(t_game *game);
int			check_open_door(int map_x, int map_y, t_game *game);
void		open_close_door(t_game *game);

#endif
