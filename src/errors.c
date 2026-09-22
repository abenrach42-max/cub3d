/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houms <houms@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/09/22 15:18:32 by houms            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *str)
{
	size_t	i;

	i = 0;
	write(2, "Error\n", 6);
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

int	is_cub(char *str)
{
	int	size;
	int	ext_len;
	int	start;

	size = ft_strlen(str);
	ext_len = ft_strlen(EXTENSION);
	if (size <= ext_len)
		return (0);
	if (ft_strncmp(str + size - ext_len, EXTENSION, ext_len) != 0)
		return (0);
	start = size - ext_len - 1;
	if (str[start] == '/' || str[start] == '.')
		return (0);
	return (1);
}
