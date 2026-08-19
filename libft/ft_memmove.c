/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:12:25 by hcissoko          #+#    #+#             */
/*   Updated: 2025/11/15 14:34:22 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;

	d = (unsigned char *) dest;
	if (!d && !(unsigned char *) src)
		return (dest);
	if (d > (unsigned char *) src)
	{
		i = n - 1;
		while (i < n)
		{
			d[i] = ((unsigned char *) src)[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = ((unsigned char *) src)[i];
			i++;
		}
	}
	return (dest);
}
