/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 10:57:12 by abenrach          #+#    #+#             */
/*   Updated: 2026/08/31 11:39:20 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_num_len(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i + len] >= '0' && str[i + len] <= '9')
		len++;
	return (len);
}

static int	parse_color_component(char *str, int *i,
		unsigned char *color_channel)
{
	int		len;
	char	*tmp;
	int		nb;

	len = get_num_len(str, *i);
	if (len == 0)
		return (-1);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, &str[*i], len + 1);
	nb = ft_atoi(tmp);
	free(tmp);
	if (nb < 0 || nb > 255)
		return (-1);
	*color_channel = nb;
	*i += len;
	return (0);
}

int	create_rgb(char *str)
{
	t_clr	clr;
	int		i;

	i = 0;
	if (parse_color_component(str, &i, &clr.r) == -1)
		return (-1);
	if (str[i] != '.')
		return (-1);
	i++;
	if (parse_color_component(str, &i, &clr.g) == -1)
		return (-1);
	if (str[i] != '.')
		return (-1);
	i++;
	if (parse_color_component(str, &i, &clr.b) == -1)
		return (-1);
	if (str[i] != '\0' && str[i] != '\n')
		return (-1);
	return (clr.r << 16 | clr.g << 8 | clr.b);
}
