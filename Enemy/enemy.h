/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:24:42 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/01 17:09:39 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_H
# define ENEMY_H

// # include "../Cubed.h"

# include "../Libraries/Mlx42/include/MLX42/MLX42.h"

typedef struct s_game t_game;

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

// static t_anim_def	g_anims[ANIM_COUNT] = {
// 	[ANIM_IDLE]		= {0, 8},
// 	[ANIM_WALK]		= {1, 8},
// 	[ANIM_ATTACK]	= {2, 13}, //row 3 & 4 unused
// 	[ANIM_HURT]		= {5, 5},
// 	[ANIM_DEATH]	= {6, 9},
// };

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
	int			health; //for later use
	int			damage; //for later use
	t_sprite	sprite;
}	t_enemy;


int		init_enemy_sprite(t_enemy *enemy, t_game *game);
void	test_sprite_loop(t_game *game);
int		init_enemy(t_game *game);

#endif