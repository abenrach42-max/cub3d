/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:40:01 by hcissoko          #+#    #+#             */
/*   Updated: 2026/05/11 21:29:58 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t		len;
	size_t		i;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &((char *) s)[i]);
		i++;
	}
}
