/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:06:39 by hcissoko          #+#    #+#             */
/*   Updated: 2025/11/12 19:07:29 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;
	size_t	total;

	i = 0;
	destlen = 0;
	while (destlen < size && dest[destlen])
		destlen++;
	srclen = ft_strlen(src);
	if (destlen < size)
	{
		while (src[i] && (i + destlen) < (size - 1))
		{
			dest[destlen + i] = src[i];
			i++;
		}
		dest[destlen + i] = '\0';
	}
	total = srclen;
	if (size < destlen)
		total += size;
	else
		total += destlen;
	return (total);
}
