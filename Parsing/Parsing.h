/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:36:06 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/09 21:30:32 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "../Cubed.h"

int		error_check(int argc, char *argv);
int		check_arg(char *str);

int		init_map(int argc, char *argv, t_game *game);
char	*get_next_line(int fd);
int		check_map_order(char **map);

int		get_textures(t_game *game);
int		get_colors(t_game *game);

int		update_map(t_game *game);

int		is_empty(char *str);
void	free_arr(char **arr);
int		arr_size(char **arr);
void	cleanup(t_game *game);

#endif
