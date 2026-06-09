/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validity.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:36:23 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/09 21:33:43 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDITY_H
#define VALIDITY_H

#include "../Cubed.h"

int		textures_exist(t_game *game);
int		player_exists(t_game *game);
int		comp_counter(char **map);

bool	flood_fill_outside(t_game *game);
bool	check_inside(char **str);

int		map_validity(t_game *game);

#endif
