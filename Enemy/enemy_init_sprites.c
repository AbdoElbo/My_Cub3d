/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:15:44 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/22 17:03:58 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

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
			// printf("Frame %d of animation %d loaded successfully!\n", f, a);
			f++;
		}
		a++;
	}
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
	sprite->anims[ANIM_DEATH]  = (t_anim_def){6, 10};
	set_animation(sprite, ANIM_IDLE);
	load_all_frames(mlx, sprite, 13);
	return (1);
}

int	init_enemy_sprite(t_game *game)
{
	t_sprite	sprite;
	int			i;

	if (game->vars.enemy_count == 0)
		return (1);
	if (!load_enemy_sprite(&sprite, game->mlx))
		return (0);
	i = 0;
	while (i < game->vars.enemy_count)
	{
		game->enemy[i].sprite = sprite;
		i++;
	}
	// printf("Enemy sprite initialized successfully!\n");
	return (1);
}
