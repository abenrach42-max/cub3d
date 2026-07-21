/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 23:09:10 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/19 20:41:02 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t          i;
    unsigned char   *p1;
    unsigned char   *p2;

    i = 0;
    p1 = (unsigned char *)s1;
    p2 = (unsigned char *)s2;
    while (i < n && (p1[i] != '\0' || p2[i] != '\0'))
    {
        if (p1[i] != p2[i])
            return (p1[i] - p2[i]);
        i++;
    }
    return (0);
}

int	is_cub(char *str)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while ((i > 0) && str[i] == ' ')
		i--;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
            && str[i - 3] == '.')
		return (1);
	return (0);
}

char    *ft_strdup(char *str)
{
    size_t  i;
    char    *dup_str;

    i = 0;
    dup_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!dup_str)
        return (NULL);
    while (str[i])
    {
        dup_str[i] = str[i];
        i++;
    }
    dup_str[i] = '\0';
    return (dup_str);
}

int tab_len(char **tab)
{
    int     i;

    i = 0;
    while (tab[i] != NULL)
        i++;
    return (i);
}

void    print_error(char *str)
{
    size_t  i;

    i = 0;
    write(2, "Error\n", 6);
    while (str[i])
    {
        write(2, &str[i], 1);
        i++;
    }
}
