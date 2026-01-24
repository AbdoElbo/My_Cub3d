/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:38:41 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/05/03 18:30:36 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pt_dst;
	const unsigned char	*pt_src;
	size_t				i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (n == 0)
		return (dst);
	pt_dst = (unsigned char *)dst;
	pt_src = (const unsigned char *)src;
	while (i < n)
	{
		pt_dst[i] = pt_src[i];
		i++;
	}
	return (dst);
}
