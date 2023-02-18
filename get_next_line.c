/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:10:38 by mwubneh           #+#    #+#             */
/*   Updated: 2023/02/18 10:35:08 by mwubneh          ###   ########.fr       */
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
	line = malloc(sizeof(char) * (i + 2));
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

static void	ft_new_buffer(char *buffer, char *temp)
{
	size_t	i;
	size_t	j;

	if (!temp)
		return ;
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	j = -1;
	if (!temp[i])
		while (++j < BUFFER_SIZE + 1)
			buffer[j] = '\0';
	i++;
	while (++j < BUFFER_SIZE + 1)
	{
		if (temp[i])
			buffer[j] = temp[i++];
		else if (!temp[i])
			buffer[j] = '\0';
	}
	free(temp);
}

static char	*ft_read(int fd, char *temp)
{
	char	s[BUFFER_SIZE + 1];
	int		rd;

	rd = 1;
	while (ft_found(temp, '\n') == 0 && rd != 0)
	{
		rd = read(fd, s, BUFFER_SIZE);
		if (rd == 0)
			break ;
		if (rd == -1)
			return (NULL);
		s[rd] = '\0';
		temp = ft_strjoin(temp, s);
	}
	return (temp);
}

static void	ft_reset_stat(char	*buffer)
{
	size_t	i;

	i = -1;
	while (++i < BUFFER_SIZE + 1)
		buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;
	char		*line;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0])
		temp = ft_strjoin(temp, buffer);
	temp = ft_read(fd, temp);
	if (!temp)
	{
		ft_reset_stat(buffer);
		return (NULL);
	}
	line = ft_get_line(temp);
	ft_new_buffer(buffer, temp);
	return (line);
}
