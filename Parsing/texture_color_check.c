/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:31:43 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/06/09 21:31:09 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.h"

static int	textures_check(char **map)
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
			break ;
		i++;
	}
	if (counter != 4)
		return (0);
	return (i);
}

static int	colors_check(char **map, int index)
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
			break ;
		i++;
	}
	if (counter != 2)
		return (0);
	return (i);
}

// static int check_map_existance(char **map, int index)
// {
// 	int	i;
// 	int	j;
// 	int	counter;

// 	i = index;
// 	counter = 0;
// 	while (is_empty(map[i]))
// 		i++;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (ft_isspace(map[i][j]))
// 			j++;
// 		if (map[i][j] == 'F' || map[i][j] == 'C')
// 			counter++;
// 		else
// 			break ;
// 		i++;
// 	}
// 	if (counter == 0)
// 		return (0);
// 	return (i);
// }

int check_map_order(char **map)
{
	int	i;
	int	j;

	i = textures_check(map);
	if (i == 0)
	{
		printf(R"Error: \nMap Not Ordered Correctly or Missing ");
		return (printf("Textures! Exiting...\n"RESET), 0);
	}
	j = colors_check(map, i);
	if (j == 0)
	{
		printf(R"Error: \nMap Not Ordered Correctly or Missing ");
		return (printf("Colors! Exiting...\n"RESET), 0);
	}
	// i = check_map_existance(map, j);
	// if (i == 0)
	// {
	// 	printf(R"Error: \nMap Doesn't");
	// 	return (printf(" exist! Exiting...\n"RESET), 0);
	// }
	return (1);
}
