/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:51:07 by abenrach          #+#    #+#             */
/*   Updated: 2025/11/26 15:10:52 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gets_line(char *tab)
{
	char	*line;
	size_t	size;
	size_t	i;

	if (!tab || !tab[0])
		return (NULL);
	i = 0;
	size = count_words(tab);
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	while (i < size)
	{
		line[i] = tab[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*join_stash(char *stash, char *buf)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buf) + 1));
	if (!tmp)
		return (free(stash), NULL);
	while (stash[i])
	{
		tmp[i] = stash[i];
		i++;
	}
	while (buf[j])
	{
		tmp[i + j] = buf[j];
		j++;
	}
	tmp[i + j] = '\0';
	return (free(stash), tmp);
}

char	*fill_tab(int fd, char *stash)
{
	char	*buf;
	int		n;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(stash), NULL);
	n = 1;
	while (!ft_strchr(stash, '\n') && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (free(buf), free(stash), NULL);
		buf[n] = '\0';
		stash = join_stash(stash, buf);
		if (!stash)
			return (free(buf), NULL);
	}
	free(buf);
	return (stash);
}

char	*update_tab(char *stash)
{
	char	*tmp;
	size_t	i;
	size_t	j;

	i = count_words(stash);
	j = 0;
	if (i >= ft_strlen(stash))
		return (free(stash), NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!tmp)
		return (free(stash), NULL);
	while (stash[i])
	{
		tmp[j] = stash[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = fill_tab(fd, stash);
	if (!stash)
		return (NULL);
	line = gets_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = update_tab(stash);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(void)
{
	int fd = open("texte.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);
	line = get_next_line(0);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}*/
