/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:31 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/28 14:16:55 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "../Cubed.h"

typedef struct s_game	t_game;
typedef struct s_files	t_files;
typedef struct s_player	t_player;

# define RADIUS 7
# define MINIMAP_SIZE 15 //(RADIUS * 2 + 1)
# define TILE_SIZE 15
# define MINIMAP_PX 225 // MINIMAP_SIZE * TILE_SIZE

void	draw_player_circle(t_game *game, int r, uint32_t color);
void	draw_enemy_circle(t_game *game, int r, double ex, double ey);
void	draw_collect_circle(t_game *game, int r, double ex, double ey);
void	draw_minimap(t_game *game);

#endif
