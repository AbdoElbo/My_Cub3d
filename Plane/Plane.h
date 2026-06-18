/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:47:31 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/18 18:39:52 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

#include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

# define RADIUS 5
# define MINIMAP_SIZE (RADIUS * 2 + 1)
# define TILE_SIZE 25

int		make_plane(t_game *game);
void	update_minimap(t_game *game);
void	draw_minimap(t_game *game);


# endif
