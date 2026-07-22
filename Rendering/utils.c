/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:45:28 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/22 16:06:30 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rendering.h"

void	order_enemy_array(t_enemy *enemies, int enemy_count)
{
	t_enemy	temp;
	int		i;
	int		j;

	i = 0;
	while (i < enemy_count)
	{
		j = i + 1;
		while(j < enemy_count)
		{
			if (enemies[j].dst_from_player > enemies[i].dst_from_player)
			{
				temp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = temp;
			}
			j++;
		}
		i++;
	}
}
