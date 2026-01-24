/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:38:16 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/05/03 19:48:10 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	space_left;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	space_left = dstsize - dst_len - 1;
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && i < space_left)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
