/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game_Dev.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:17:07 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/10 20:13:40 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEH_H
# define GAME_DEH_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

// typedef enum e_weapons
// {
// 	SWORD,
// 	OTHER,
// }	t_weapons;

void		move_player(t_game *game);
void		ft_mouse_mvm(double x, double y, void *param);
void		rotate_player(t_game *game);
void		draw_line(t_game *game, uint32_t color);
void		gun_dev(t_game *game);

int			load_tex(t_game *game);
long long	get_time_in_ms(void);

# endif
