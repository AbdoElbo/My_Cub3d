/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:46:33 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/28 19:37:13 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	digit_count(int a)
{
	int		count;
	long	num;

	count = 0;
	num = a;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		count++;
		num = -num;
	}
	while (num > 0)
	{
		count++;
		num = num / 10;
	}
	return (count);
}

static uint32_t	get_rgb_color(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

static int	get_floor_color(t_game *game, int i, int j)
{
	static int	counter;
	int			r;
	int			g;
	int			b;
	char		*str;

	counter++;
	str = game->map[i];
	while (ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (printf("Error:\nNo Floor Color Found!\n"), 0);
	if (counter > 1)
		return (printf("Error:\nDuplicated Floor color\n"), 0);
	r = ft_atoi(&str[j]);
	j += digit_count(r) + 1;
	g = ft_atoi(&str[j]);
	j += digit_count(g) + 1;
	b = ft_atoi(&str[j]);
	game->floor_color = get_rgb_color(r, g, b);
	return (1);
}

static int	get_ceiling_color(t_game *game, int i, int j)
{
	static int	counter;
	int			r;
	int			g;
	int			b;
	char		*str;

	counter++;
	str = game->map[i];
	while (ft_isspace(str[j]))
		j++;
	if (!str[j])
		return (printf("Error:\nNo Ceiling Color Found!\n"), 0);
	if (counter > 1)
		return (printf("Error:\nDuplicated Ceiling color\n"), 0);
	r = ft_atoi(&str[j]);
	j += digit_count(r) + 1;
	g = ft_atoi(&str[j]);
	j += digit_count(g) + 1;
	b = ft_atoi(&str[j]);
	game->ceiling_color = get_rgb_color(r, g, b);
	return (1);
}

int	get_colors(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (ft_isspace(game->map[i][j]))
			j++;
		if (game->map[i][j] == 'F')
		{
			if (!get_floor_color(game, i, j + 1))
				return (0);
		}
		if (game->map[i][j] == 'C')
		{
			if (!get_ceiling_color(game, i, j + 1))
				return (0);
		}
		i++;
	}
	return (1);
}
