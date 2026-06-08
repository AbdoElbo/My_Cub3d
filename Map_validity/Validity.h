/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validity.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:36:23 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/08 18:32:14 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDITY_H
#define VALIDITY_H

#include "../Cubed.h"

int	    player_exists(t_game *game);
int	    comp_counter(char **map);

bool	flood_fill_outside(t_game *game);
bool	flood_fill_inside(t_game *game);

int		map_validity(t_game *game);

#endif
