/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game_Dev.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:17:07 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/19 17:20:59 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_DEH_H
# define GAME_DEH_H

# include "../Cubed.h"

typedef struct s_game	t_game ;
typedef struct s_files	t_files ;
typedef struct s_player	t_player ;

void	move_forwards(t_game *game);
void	move_backwards(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);


# endif
