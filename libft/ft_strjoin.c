/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:32:34 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/05/13 18:20:12 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	int		total;

	total = ft_strlen(s1) + ft_strlen(s2);
	joint = malloc(sizeof(char) * (total + 1));
	if (joint == NULL)
		return (NULL);
	joint[0] = '\0';
	ft_strlcat(joint, s1, total + 1);
	ft_strlcat(joint, s2, total + 1);
	return (joint);
}
