/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validity.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 12:36:23 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/30 16:31:07 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDITY_H
# define VALIDITY_H

# include "../Cubed.h"

typedef struct s_game	t_game;
typedef struct s_files	t_files;
typedef struct s_player	t_player;

int	textures_exist(t_game *game);
int	player_exists(t_game *game);
int	comp_counter(char **map);

int	flood_fill_outside(t_game *game);
int	check_inside(char **str);
int	map_validity(t_game *game);

#endif
