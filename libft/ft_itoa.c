/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:32:36 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/05/06 21:53:02 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
{
	int		space_needed;
	char	*str;
	long	num;

	num = n;
	space_needed = digit_count(num);
	str = malloc(sizeof(char) * (space_needed + 1));
	if (str == NULL)
		return (NULL);
	str[space_needed--] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[space_needed--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
