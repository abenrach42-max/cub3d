/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 12:34:42 by hcissoko          #+#    #+#             */
/*   Updated: 2025/12/10 14:45:16 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_affect_temp(char *temp, char *buffer)
{
	char	*save;

	save = NULL;
	if (temp)
	{
		save = ft_strdup(temp);
		free(temp);
		temp = ft_strjoin(save, buffer);
		free(save);
	}
	else
		temp = ft_strdup(buffer);
	return (temp);
}

void	ft_extract_ln(char **ptr_temp)
{
	char	*keep_temp;

	keep_temp = ft_strdup(ft_strchr(*ptr_temp, '\n') + 1);
	free(*ptr_temp);
	*ptr_temp = keep_temp;
}

static char	*ft_clear_gnl(char **ptr_temp, char **ptr_buffer, char *line)
{
	if (ptr_temp && *ptr_temp)
	{
		free(*ptr_temp);
		*ptr_temp = NULL;
	}
	if (ptr_buffer && *ptr_buffer)
	{
		free(*ptr_buffer);
		*ptr_buffer = NULL;
	}
	return (line);
}
/*
We use ptr to free in the function
There is 3 cases
- EOF so we free all and line = temp
- Text contain \n so we return only the text before \n
- Empty text
*/

char	*ft_getline(char **ptr_temp, char **ptr_buffer, int bytes_read)
{
	char	*line;
	int		end;

	line = NULL;
	if (!ptr_temp || !ptr_buffer || !*ptr_temp)
		return (ft_clear_gnl(ptr_temp, ptr_buffer, NULL));
	if (*ptr_temp && **ptr_temp && bytes_read == 0)
		line = ft_strdup(*ptr_temp);
	if (*ptr_temp && ft_strchr(*ptr_temp, '\n'))
	{
		end = ft_strlen(*ptr_temp) - ft_strlen(ft_strchr(*ptr_temp, '\n')) + 1;
		line = ft_substr(*ptr_temp, 0, end);
		ft_extract_ln(ptr_temp);
		return (line);
	}
	return (ft_clear_gnl(ptr_temp, ptr_buffer, line));
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	int			bytes_read;

	if (fd == -1 && temp)
		return (free(temp), temp = NULL, NULL);
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	bytes_read = 1;
	buffer = NULL;
	while (0 < bytes_read)
	{
		if (temp && ft_strchr(temp, '\n'))
			return (ft_getline(&temp, &buffer, bytes_read));
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 1)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_affect_temp(temp, buffer);
		free(buffer);
	}
	return (ft_getline(&temp, &buffer, bytes_read));
}
