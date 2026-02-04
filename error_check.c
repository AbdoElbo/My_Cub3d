/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:31:43 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/02/04 14:12:31 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
