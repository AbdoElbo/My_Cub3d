/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:36:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/05 11:53:48 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../Cubed.h"

char		*get_next_line(int fd);
int			check_arg(char *str);
int			error_check(int argc, char *argv);
void		init_vars(t_game *game);
int			check_map_order(char **map);
int			directions_check(char **map);
int			colors_check(char **map, int index);
int			get_textures(t_game *game);
uint32_t	get_rgb_color(int r, int g, int b);
int			get_colors(t_game *game);
int			is_empty(char *str);
void		free_arr(char **arr);
int			arr_size(char **arr);
void		cleanup(t_game *game);

#endif
