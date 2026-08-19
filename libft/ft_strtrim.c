/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:57:02 by hcissoko          #+#    #+#             */
/*   Updated: 2026/05/11 21:42:04 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include "libft.h"
#include <stdio.h>

int	ft_incharset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	size_t	i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	i = 0;
	while (ft_incharset(s1[start], set))
		start++;
	while (ft_incharset(s1[end], set))
		end--;
	if (start <= end)
		str = malloc(sizeof(char) * (end - start + 2));
	else
		str = malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	while (start <= end && s1[start])
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
