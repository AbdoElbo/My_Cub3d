/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_Movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:16:42 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/27 17:57:04 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h"

static void	go_to_player(t_game *game, t_player *player, t_enemy *enemy)
{
	float	nx;
	float	ny;
	float	dx;
	float	dy;

	dx = player->x - enemy->x;
	dy = player->y - enemy->y;
	enemy->angle = atan2f(dy, dx);
	enemy->dir_x = cosf(enemy->angle);
	enemy->dir_y = sinf(enemy->angle);
	// printf("enemy angle is %f\n", enemy->angle * 57.29578f);
	nx = enemy->x + enemy->dir_x * 0.01f;
	ny = enemy->y + enemy->dir_y * 0.01f;
	if (!hits_wall(game, nx, enemy->y))
		enemy->x = nx;
	if (!hits_wall(game, enemy->x, ny))
		enemy->y = ny;
}

static void	update_dst_from_player(t_player *p, t_enemy *e)
{
	float	distance;

	// Pythogoras theorum just to calculate the distance from the enemt to the playah
	// square root of (x1 - x2)^2 + (y1 - y2)^2
	distance = sqrtf((e->x - p->x) * (e->x - p->x)
		+ (e->y - p->y) * (e->y - p->y));
	e->dst_from_player = distance;
}

static void	check_get_damaged(t_game *game, int i)
{
	if (game->enemy[i].sprite.current_frame == 9
		&& game->vars.last_hit == 0 && game->enemy->health != 0 && game->enemy[i].visible)
	{
		game->vars.last_hit = get_time_in_ms();
		game->images.getting_hurt->enabled = true;
		if (game->player.health - ENEMY_DAMAGE <= 0)
		{
			game->player.health = 0;
			printf("PLAYER DIED, RIP!!\n");
		}
		else
		{
			game->player.health -= ENEMY_DAMAGE;
			printf("Player took %d damage\n", ENEMY_DAMAGE);
			game->enemy[i].attack_start = get_time_in_ms();
		}
	}
}

static void	check_hit_invisible(t_game *game, t_enemy *enemy)
{
	long long	now;
	long long	frame_duration;

	if ((enemy->aim_angle < -FOV / 2 || enemy->aim_angle > FOV / 2)
			&& enemy->visible)
	{
		frame_duration = 2400;
		now = get_time_in_ms();
		if (now - enemy->attack_start < frame_duration)
			return ;
		game->images.getting_hurt->enabled = false;
		game->vars.last_hit = get_time_in_ms();
		game->images.getting_hurt->enabled = true;
		if (game->player.health - ENEMY_DAMAGE <= 0)
		{
			game->player.health = 0;
			printf("PLAYER DIED, RIP!!\n");
		}
		else
		{
			game->player.health -= ENEMY_DAMAGE;
			enemy->attack_start = get_time_in_ms();
			printf("Player took %d damage\n", ENEMY_DAMAGE);
		}
	}
}

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->vars.enemy_count)
	{
		update_dst_from_player(&game->player, &game->enemy[i]);
		if (game->enemy[i].dst_from_player < 5)
		{
			if (game->enemy[i].dst_from_player >= 0.8f)
				go_to_player(game, &game->player, &game->enemy[i]);
			if (game->enemy[i].dst_from_player < 2 && game->movement == FREE
				&& game->enemy[i].health)
			{
				check_hit_invisible(game, &game->enemy[i]);
				set_animation(&game->enemy[i].sprite, ANIM_ATTACK);
				check_get_damaged(game, i);
			}
			else if (game->enemy[i].dst_from_player >= 2 && game->movement == FREE)
				set_animation(&game->enemy[i].sprite, ANIM_IDLE);
		}
		i++;
	}
}


