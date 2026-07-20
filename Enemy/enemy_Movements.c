/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_Movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:16:42 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/20 16:52:30 by aelbouaz         ###   ########.fr       */
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

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->vars.enemy_count)
	{
		update_dst_from_player(&game->player, &game->enemy[i]);
		if (game->enemy[i].dst_from_player < 5
			&& game->enemy[i].dst_from_player > 0.4f)
		{
			go_to_player(game, &game->player, &game->enemy[i]);
			if (game->enemy[i].dst_from_player < 1)
				set_animation(&game->enemy[i].sprite, ANIM_ATTACK);
		}
		i++;
	}
}
