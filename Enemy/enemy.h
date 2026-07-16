/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:24:42 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/16 17:04:52 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

typedef enum e_anim
{
	ANIM_IDLE = 0,
	ANIM_WALK,
	ANIM_ATTACK,
	ANIM_HURT,
	ANIM_DEATH,
	ANIM_COUNT
}	t_anim;

typedef struct s_anim_def
{
	int	row;
	int	frame_count;
}	t_anim_def;

typedef struct s_sprite
{
	mlx_texture_t	*sheet;
	mlx_image_t		**frames; // array of images, one per frame
	t_anim			current_anim;
	int				current_frame;
	int				frame_w;
	int				frame_h;
	double			frame_timer;
	double			frame_duration; // seconds per frame, e.g. 0.1
	t_anim_def		anims[ANIM_COUNT];
}	t_sprite;

typedef struct s_enemy
{
	float		x;
	float		y;
	float		dir_x;
	float		dir_y;
	float		angle;
	int			health; //for later use
	int			damage; //for later use
	float		dst_from_player;
	t_sprite	sprite;
}	t_enemy;

int		init_enemy(t_game *game);
int		init_enemy_sprite(t_game *game);
void	set_animation(t_sprite *sprite, t_anim anim);
void	test_sprite_loop(t_game *game, t_enemy *enemy);
void	destroy_enemy_sprite(t_sprite *sprite, mlx_t *mlx);
void	move_enemies(t_game *game);

#endif
