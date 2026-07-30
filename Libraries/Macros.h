/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:11:56 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/30 18:47:10 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define BUFFER_SIZE 200
// we'll limit this to the limit we put ourselves, so we'll always do one read()
// and we don't have to realloc again
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 700
# define MAX_WIDTH SCREEN_WIDTH
# define MAX_HEIGHT SCREEN_HEIGHT
# define NUM_RAYS SCREEN_WIDTH
# define FOV 1.5707963268 // PI / 2

# define PLAYER_HEALTH 100
# define KATANA_DAMAGE 40
# define KATANA_FIELD FOV
# define SHOTGUN_FIELD 0.3 //FOV / 2
# define SHOTGUN_DAMAGE 35
# define ENEMY_HEALTH 100
# define ENEMY_DAMAGE 20

# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"
# define R "\033[1;31m"
# define RESET "\033[0m"

#endif
