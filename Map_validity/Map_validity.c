/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:38:34 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/08 18:34:18 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Validity.h"

int	map_validity(t_game *game)
{
	int	p_exist;
	
	p_exist = player_exists(game);
	if (p_exist > 1)
		return (printf("ERROR, Multiple players found! Exiting..."), 0);
	else if (p_exist == 0)
		return (printf("ERROR, No Player Found! Exiting..."), false);
	if (!player_exists(game))
		return (0);
	if (!flood_fill_outside(game))
		return (0);
	
	// if (!flood_fill_inside(game))
	// 	return (0);
	
	return (1);
}
