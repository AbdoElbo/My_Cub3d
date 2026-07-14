/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:24:39 by lpieck            #+#    #+#             */
/*   Updated: 2026/07/14 14:22:47 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"
#include "../Cubed.h"
//INITIALIZE ENEMY

void	set_animation(t_sprite *sprite, t_anim anim)
{
	if (sprite->current_anim == anim)
		return ;
	sprite->current_anim = anim;
	sprite->current_frame = 0;
	sprite->frame_timer = 0.0;
	printf("Animation set successfully!\n");
}

void	destroy_enemy_sprite(t_sprite *sprite, mlx_t *mlx)
{
	int	i;

	if (!sprite)
		return ;
	i = 0;
	while (i < ANIM_COUNT * 13)
	{
		if (sprite->frames && sprite->frames[i])
			mlx_delete_image(mlx, sprite->frames[i]);
		i++;
	}
	free(sprite->frames);
	if (sprite->sheet)
		mlx_delete_texture(sprite->sheet);
}

t_enemy assign_values_to_enemy(int x, int y)
{
	t_enemy new_enemy;
	
	new_enemy.x = x + 0.5f;
	new_enemy.y = y + 0.5f;
	new_enemy.health = 3;
	new_enemy.damage = 1;
	new_enemy.sprite.sheet = NULL;
	new_enemy.sprite.frames = NULL;
	return(new_enemy);
}

static void	look_for_enemy_coordinates(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'V')
			{
				if (k >= game->enemy_count)
					return ;
				game->enemy[k] = assign_values_to_enemy(j, i);
				game->map[i][j] = '0';
				k++;
			}
			j++;
		}
		i++;
	}
}

static void extract_frame(t_sprite *sprite, int f, int a)
{
	uint8_t *pixel;
	uint32_t color;
	int x;
	int y;

	y = 0;
	while (y < sprite->frame_h)
	{
		x = 0;
		while (x < sprite->frame_w)
		{
			pixel = &sprite->sheet->pixels[((sprite->anims[a].row * sprite->frame_h + y) * sprite->sheet->width+ (f * sprite->frame_w + x)) * 4];
			color = (uint32_t)pixel[0] << 24 | (uint32_t)pixel[1] << 16
				| (uint32_t)pixel[2] << 8 | (uint32_t)pixel[3];
			mlx_put_pixel(sprite->frames[a * 13 + f], x, y, color);
			x++;
		}
		y++;
	}
}

static void	load_all_frames(mlx_t *mlx, t_sprite *sprite, int max_frames)
{
	int a;
	int f;

	a = 0;
	while (a < ANIM_COUNT)
	{
		f = 0;
		while (f < sprite->anims[a].frame_count && f < max_frames)
		{
			sprite->frames[a * max_frames + f] = mlx_new_image(mlx, sprite->frame_w, sprite->frame_h);
			extract_frame(sprite, f, a);
			f++;
		}
		a++;
	}
}

void	update_sprite(t_sprite *s, double dt)
{
	t_anim_def	*def;

	s->frame_timer += dt;
	if (s->frame_timer < s->frame_duration)
		return ;
	s->frame_timer = 0.0;
	def = &s->anims[s->current_anim];
	if (s->current_anim == ANIM_HURT || s->current_anim == ANIM_DEATH) // oneshot hurt and death animations
	{
		if (s->current_frame < def->frame_count - 1)
			s->current_frame++;
		return ;
	}
	s->current_frame = (s->current_frame + 1) % def->frame_count;
}

static int	load_enemy_sprite(t_sprite *sprite, mlx_t *mlx)
{
	sprite->frame_w = 160;
	sprite->frame_h = 128;
	sprite->frame_duration = 0.1;
	sprite->sheet = mlx_load_png("Resources/textures/enemy.png");
	if (!sprite->sheet)
		return (0);
	sprite->frames = ft_calloc(ANIM_COUNT * 13, sizeof(mlx_image_t *));
	if (!sprite->frames)
	{
		mlx_delete_texture(sprite->sheet);
		return (0);
	}
	sprite->anims[ANIM_IDLE]   = (t_anim_def){0, 8};
	sprite->anims[ANIM_WALK]   = (t_anim_def){1, 8};
	sprite->anims[ANIM_ATTACK] = (t_anim_def){2, 13};
	sprite->anims[ANIM_HURT]   = (t_anim_def){5, 5};
	sprite->anims[ANIM_DEATH]  = (t_anim_def){6, 9};
	set_animation(sprite, ANIM_IDLE);
	load_all_frames(mlx, sprite, 13);
	return (1);
}

int init_enemy(t_game *game)
{
	printf("Amount of enemies: %d\n", game->enemy_count);
	if (game->enemy_count <= 0)
	{
		game->enemy = NULL;
		return (1);
	}
	game->enemy = ft_calloc(game->enemy_count, sizeof(t_enemy));
	if (!game->enemy)
		return (0);
	look_for_enemy_coordinates(game);
	return (1);
}

int init_enemy_sprite(t_game *game)
{
	t_sprite	sprite;
	int			i;
	
	if (!game->enemy || game->enemy_count <= 0)
		return (1);
	if (!load_enemy_sprite(&sprite, game->mlx))
		return (0);
	i = 0;
	while (i < game->enemy_count)
	{
		game->enemy[i].sprite = sprite;
		i++;
	}
	printf("Enemy sprite initialized successfully!\n");
	return (1);
}

mlx_image_t	*get_current_frame(t_sprite *s, int max_frames)
{
	return (s->frames[s->current_anim * max_frames + s->current_frame]);
}

void	test_sprite_loop(t_game *game)
{
	mlx_image_t	*frame;
	uint32_t	*src;
	uint32_t	*dst;
	uint32_t	y;
	uint32_t	x;

	if (!game->enemy || game->enemy_count <= 0)
		return ;
	update_sprite(&game->enemy[0].sprite, game->mlx->delta_time);
	frame = get_current_frame(&game->enemy[0].sprite, 13);
	src = (uint32_t *)frame->pixels;
	dst = (uint32_t *)game->framebuf->pixels;
	y = 0;
	while (y < frame->height)
	{
		x = 0;
		while (x < frame->width)
		{
			if (src[y * frame->width + x] & 0xFF)
				dst[y * game->framebuf->width + x] = src[y * frame->width + x];
			x++;
		}
		y++;
	}
}
