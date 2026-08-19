/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:27:08 by hcissoko          #+#    #+#             */
/*   Updated: 2026/01/26 15:56:00 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putnbr_base(unsigned long nb, char type)
{
	unsigned long	x;
	int				len;
	char			c;
	char			*base;

	if (type == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = 0;
	x = nb;
	if (x / 16 > 0)
	{
		len += ft_putnbr_base(x / 16, type);
	}
	c = base[x % 16];
	write(1, &c, 1);
	len++;
	return (len);
}
