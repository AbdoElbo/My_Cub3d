/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpieck <lpieck@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:51:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/13 18:09:34 by lpieck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
#define BONUS_H

#include "../Cubed.h"


typedef struct s_game	t_game;
typedef struct s_files	t_files;
typedef struct s_player	t_player;


typedef struct s_door
{
	int				x;
	int				y;
	bool			open;
}	t_door;

int init_doors(t_game *game);
int check_open_door(int map_x, int map_y, t_game *game);
void open_close_door(t_game *game);

#endif
