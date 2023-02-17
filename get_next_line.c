/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:10:38 by mwubneh           #+#    #+#             */
/*   Updated: 2023/02/17 16:48:39 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char *s)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_new_str(char str[BUFFER_SIZE + 1], char *temp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!temp)
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
		while (j < BUFFER_SIZE + 1)
		{
			str[j] = '\0';
			j++;
		}
	i++;
	while (j < BUFFER_SIZE)
	{
		if (temp[i])
			str[j++] = temp[i++];
		else if (!temp[i])
			str[j++] = '\0';
	}
	free(temp);
	return (str);
}

static char	*ft_read(int fd, char *temp)
{
	char	*s;
	int		rd;

	s = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!s)
		return (NULL);
	rd = 1;
	while (ft_found(temp, '\n') == 0 && rd != 0)
	{
		rd = read(fd, s, BUFFER_SIZE);
		if (rd == -1)
		{
			free(s);
			return (NULL);
		}
		s[rd] = '\0';
		temp = ft_strjoin(temp, s);
	}
	free(s);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE + 1];
	char		*temp;
	char		*line;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str[0])
		temp = ft_strjoin(temp, str);
	temp = ft_read(fd, temp);
	if (!temp)
		return (NULL);
	line = ft_get_line(temp);
	ft_new_str(str, temp);
	return (line);
}
