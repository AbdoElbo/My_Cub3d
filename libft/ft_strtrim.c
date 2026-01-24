/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:32:36 by aelbouaz          #+#    #+#             */
/*   Updated: 2025/05/06 21:59:30 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static int	check_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && ft_strchr(set, s1[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*pt;
	int		start;
	int		end;
	int		n;

	if (!s1)
		return (NULL);
	if (!set || !*set || s1[0] == '\0')
		return (ft_strdup(s1));
	start = check_start(s1, set);
	end = check_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	n = 0;
	pt = malloc(sizeof(char) * (end - start + 2));
	if (pt == NULL)
		return (NULL);
	while (start <= end)
		pt[n++] = s1[start++];
	pt[n] = '\0';
	return (pt);
}
