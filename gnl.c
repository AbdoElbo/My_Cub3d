/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaz <aelbouaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:14:41 by aelbouaz          #+#    #+#             */
/*   Updated: 2026/01/26 16:14:44 by aelbouaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	update_leftover(char **leftover)
{
	int		i;
	int		n;
	char	*leftover_tmp;

	i = 0;
	while ((*leftover)[i] && (*leftover)[i] != '\n')
		i++;
	if ((*leftover)[i] == '\n')
		i++;
	leftover_tmp = malloc(ft_strlen(*leftover) - i + 1);
	if (!leftover_tmp)
		return (0);
	n = 0;
	while ((*leftover)[i])
		leftover_tmp[n++] = (*leftover)[i++];
	leftover_tmp[n] = '\0';
	free(*leftover);
	*leftover = ft_strdup(leftover_tmp);
	if (!(*leftover))
		return (free(leftover_tmp), 0);
	if (!ft_strlen(*leftover))
		return (free(*leftover), *leftover = NULL, free(leftover_tmp), 1);
	return (free(leftover_tmp), 1);
}

char	*extract_str(char *leftover)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	n = 0;
	while (leftover[i] && leftover[i] != '\n')
		str[n++] = leftover[i++];
	if (leftover[i] == '\n')
		str[n++] = leftover[i++];
	str[n] = '\0';
	return (str);
}

int	read_into_leftover(char **leftover, int fd)
{
	char	*tmp;
	char	*new_leftover;
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr((*leftover), '\n'))
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (!tmp)
			return (0);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(tmp), 0);
		tmp[bytes_read] = '\0';
		new_leftover = ft_strjoin(*leftover, tmp);
		if (!new_leftover)
			return (free(tmp), 0);
		free(*leftover);
		*leftover = ft_strdup(new_leftover);
		free(new_leftover);
		free(tmp);
		if (!(*leftover) || bytes_read < BUFFER_SIZE)
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftover)
	{
		leftover = ft_strdup("");
		if (!leftover)
			return (NULL);
	}
	if (!read_into_leftover(&leftover, fd))
		return (free(leftover), leftover = NULL, NULL);
	if (leftover)
	{
		line = extract_str(leftover);
		if (!line)
			return (free(leftover), leftover = NULL, NULL);
		if (!update_leftover(&leftover))
			return (free(leftover), leftover = NULL, free(line), NULL);
		if (line && !line[0])
			return (free(leftover), leftover = NULL, free(line), NULL);
		return (line);
	}
	return (NULL);
}
