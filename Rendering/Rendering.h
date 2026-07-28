/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 12:53:28 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/28 15:33:05 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_enemy	t_enemy;
typedef struct s_player	t_player ;
typedef struct s_ray	t_ray ;

typedef struct s_draw_params
{
	int	col;
	int	line_height;
	int	draw_start;
	int	draw_end;
}	t_draw_params;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	raw_dist;
	double	hit_x;
	double	hit_y;
}	t_dda;

typedef enum e_sprite_kind
{
	SPRITE_ENEMY,
	SPRITE_COLLECT,
}	t_sprite_kind;

typedef struct s_sprite_draw
{
	t_sprite_kind	kind;
	void			*ptr;
	double			depth;
}	t_sprite_draw;

double	hit_wall_x(t_dda *dda, t_ray *ray, t_game *game);
void	init_delta_dist(t_dda *dda, t_ray *ray);
void	render_frame(t_game *game);
void	cast_rays(t_game *game);
void	order_enemy_array(t_enemy *enemies, int enemy_count);
void	render_sprite_queue(t_game *game);

#endif
