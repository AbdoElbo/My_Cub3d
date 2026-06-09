/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:31:43 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/09 15:01:53 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

int	check_arg(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (!len)
		return (0);
	if (str[len] == 'b')
	{
		len--;
		if (str[len] == 'u')
		{
			len--;
			if (str[len] == 'c')
			{
				len--;
				if (str[len] == '.')
					return (1);
			}
		}
	}
	return (0);
}

int	error_check(int argc, char *argv)
{
	if (argc != 2)
	{
		printf("enter correct number of Args\n");
		printf("Example : ./cubed maps/map1.cub\n");
		return (0);
	}
	if (!check_arg(argv))
	{
		printf("Wrong File Bruh\n");
		printf("Format *.cub\n");
		return (0);
	}
	return (1);
}

int check_map_order(char **map)
{
	int	i;
	int	j;

	i = directions_check(map);
	if (i == 0)
		return (printf("(DIRECTIONS) Map is Not Oredered Correctly or Missing Directions! Exiting...\n"), 0);
	j = colors_check(map, i);
	if (j == 0)
		return (printf("(COLORS) Map is Not Oredered Correctly or Missing colors! Exiting...\n"), 0);
	return (1);
}

int	directions_check(char **map)
{
	int	i;
	int	j;
	int	counter;

	i = 0;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (is_empty(map[i]))
			i++;
		while (ft_isspace(map[i][j]))
			j++;
		if (map[i][j] == 'N' || map[i][j] == 'W'
			|| map[i][j] == 'E' || map[i][j] == 'S')
			counter++;
		else
			return (0);
		i++;
		if (counter == 4)
			break;
	}
	if (counter != 4)
		return (0);
	return (i);
}

int	colors_check(char **map, int index)
{
	int	i;
	int	j;
	int	counter;

	i = index;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (is_empty(map[i]))
			i++;
		while (ft_isspace(map[i][j]))
			j++;
		if (map[i][j] == 'F' || map[i][j] == 'C')
			counter++;
		else
			return (0);
		i++;
		if (counter == 2)
			break;
	}
	if (counter != 2)
		return (0);
	return (i);
}
