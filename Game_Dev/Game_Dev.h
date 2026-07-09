/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game_Dev.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:17:07 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/09 18:36:54 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEH_H
# define GAME_DEH_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

typedef enum s_guns
{
	PISTOL,
	UZI,
	AK47,
}	t_guns;

void	move_player(t_game *game);
void	ft_mouse_mvm(double x, double y, void *param);
void	rotate_player(t_game *game);
void	draw_line(t_game *game, uint32_t color);
void	gun_dev(t_game *game);

int		load_pistol_tex(t_game *game);
int		load_uzi_tex(t_game *game);
int		load_ak47_tex(t_game *game);

# endif
