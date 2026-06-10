/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:38:43 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/05/03 16:10:14 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pt_dst;
	const unsigned char	*pt_src;
	size_t				i;

	pt_dst = (unsigned char *)dst;
	pt_src = (const unsigned char *)src;
	if (pt_src < pt_dst && pt_src + len > pt_dst)
	{
		i = len - 1;
		while (i > 0)
		{
			pt_dst[i] = pt_src[i];
			i--;
		}
		pt_dst[0] = pt_src[0];
		return (dst);
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
