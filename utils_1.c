/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/09/12 17:54:52 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

int	check_arg(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
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
				{
					if (!len)
						return (0);
					else
						return (1);
				}
			}
		}
	}
	return (0);
}

// int	read_into_map(char **map, int fd)
// {
// 	char	*tmp;
// 	char	*new_map;
// 	int		bytes_read;

// 	bytes_read = 1;
// 	while (bytes_read > 0)
// 	{
// 		tmp = malloc(BUFFER_SIZE + 1);
// 		if (!tmp)
// 			return (0);
// 		bytes_read = read(fd, tmp, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 			return (free(tmp), 0);
// 		tmp[bytes_read] = '\0';
// 		new_map = ft_strjoin(*map, tmp);
// 		if (!new_map)
// 			return (free(tmp), 0);
// 		free(*map);
// 		*map = ft_strdup(new_map);
// 		free(new_map);
// 		free(tmp);
// 	}
// 	return (1);
// }

// int	width_size(char *map)
// {
// 	int	i;
// 	int	width;

// 	i = 0;
// 	width = 0;
// 	while (map[i] == '1')
// 	{
// 		width++;
// 		i++;
// 	}
// 	return (width * 100);
// }

// int	height_size(char *map)
// {
// 	int	i;
// 	int	height;

// 	i = 0;
// 	height = 0;
// 	while (map[i])
// 	{
// 		if (map[i] == '\n')
// 			height++;
// 		i++;
// 	}
// 	return (height * 100);
// }
