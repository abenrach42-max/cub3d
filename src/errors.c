/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houms <houms@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/09/10 13:23:12 by houms            ###   ########.fr       */
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
	size_t	i;

	if (ft_strlen(str) < 4)
		return (1);
	i = ft_strlen(str) - 1;
	while ((i > 0) && str[i] == ' ')
		i--;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
		&& str[i - 3] == '.')
		return (0);
	return (1);
}
