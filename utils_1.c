/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:29:01 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 16:32:06 by aelbouaz         ###   ########.fr       */
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
