/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 19:58:40 by hcissoko          #+#    #+#             */
/*   Updated: 2026/05/11 21:29:02 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_strdup_split(char *src, char c)
{
	char		*dup;
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	while (src[len] && src[len] != c)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**ft_strsmalloc(char *str, char c)
{
	size_t		i;
	size_t		words;
	char		**strs;

	i = 0;
	words = 0;
	while (str[i])
	{
		if ((str[i] != c) && (i == 0 || str[i - 1] == c))
		{
			words++;
		}
		i++;
	}
	strs = malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	return (strs);
}

char	**ft_split(char *str, char c)
{
	size_t		i;
	size_t		j;
	char		**strs;

	i = 0;
	j = 0;
	strs = ft_strsmalloc(str, c);
	if (!strs)
		return (NULL);
	while (str[i])
	{
		if ((str[i] != c) && (i == 0 || str[i - 1] == c))
		{
			strs[j] = ft_strdup_split(str + i, c);
			if (!strs[j])
			{
				ft_strsfree(strs, j);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	strs[j] = 0;
	return (strs);
}
