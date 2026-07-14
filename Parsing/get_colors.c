/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:46:33 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/07/14 13:21:22 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

uint32_t	get_rgb_color(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

static int  has_invalid_chars(char *str)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int  get_floor_color(t_game *game, int i, int j)
{
	static int  counter;
	int		r;
	int		g;
	int		b;
	char	**arr;

	counter++;
	arr = ft_split(&game->map[i][j + 1], ',');
	if (!arr)
		return (printf(Y"Error:\nNo Floor Color Found!\n"RESET), 0);
	if (counter > 1)
		return (free_arr(arr), printf(Y"Error:\nDuplicated F color\n"RESET), 0);
	if (arr_size(arr) != 3)
		return (free_arr(arr), printf(Y"Error:\nRGB Incorrect num\n"RESET), 0);
	if (has_invalid_chars(arr[0]) || has_invalid_chars(arr[1])
		|| has_invalid_chars(arr[2]))
		return (free_arr(arr), printf(Y"Error:\nRGB invalid values\n"RESET), 0);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (free_arr(arr), printf(Y"Error:\nWrong RGB values\n"RESET), 0);
	game->floor_color = get_rgb_color(r, g, b);
	return (free_arr(arr), 1);
}

static int  get_ceiling_color(t_game *game, int i, int j)
{
	static int  counter;
	int		r;
	int		g;
	int		b;
	char	**arr;

	counter++;
	arr = ft_split(&game->map[i][j + 1], ',');
	if (!arr)
		return (printf(Y"Error:\nNo Floor Color Found!\n"RESET), 0);
	if (counter > 1)
		return (free_arr(arr), printf(Y"Error:\nDuplicated C color\n"RESET), 0);
	if (arr_size(arr) != 3)
		return (free_arr(arr), printf(Y"Error:\nRGB Incorrect num\n"RESET), 0);
	if (has_invalid_chars(arr[0]) || has_invalid_chars(arr[1])
		|| has_invalid_chars(arr[2]))
		return (free_arr(arr), printf(Y"Error:\nRGB invalid values\n"RESET), 0);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (free_arr(arr), printf(Y"Error:\nWrong RGB values\n"RESET), 0);
	game->ceiling_color = get_rgb_color(r, g, b);
	return (free_arr(arr), 1);
}

int get_colors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (ft_isspace(game->map[i][j]))
			j++;
		if (game->map[i][j] == 'F' && !get_floor_color(game, i, j + 1))
			return (0);
		else if (game->map[i][j] == 'C' && !get_ceiling_color(game, i, j + 1))
			return (0);
		else if (game->map[i][j] == '1' && game->map_start == -1)
			game->map_start = i;
		i++;
	}
	if (game->map_start == -1)
		return (printf(Y"Error:\n(MAP) Map Not Found!! Exiting...\n"RESET), 0);
	return (1);
}
