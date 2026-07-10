/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:51:46 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/05 17:13:23 by aelbouaz         ###   ########.fr       */
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

#endif
