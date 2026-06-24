/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekko <gekko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:31 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/23 20:54:43 by gekko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

# define RADIUS 5
# define MINIMAP_SIZE (RADIUS * 2 + 1)
# define TILE_SIZE 25

// void    minimap_update(t_game *game);
void	draw_minimap(t_game *game);

# endif
