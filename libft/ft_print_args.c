/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:38:22 by hcissoko          #+#    #+#             */
/*   Updated: 2026/03/30 20:00:25 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	ft_print_c(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_print_p(unsigned long nb, int fd)
{
	if (nb == 0)
		return (ft_print_s("(nil)", fd));
	ft_putstr_fd("0x", fd);
	return (2 + ft_putnbr_base(nb, 'p'));
}

int	ft_print_args(va_list args, char type, int fd)
{
	if (type == 's')
		return (ft_print_s(va_arg(args, char *), fd));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (type == 'c')
		return (ft_print_c(va_arg(args, int), fd));
	else if (type == '%')
		return (ft_print_c('%', fd));
	else if (type == 'x' || type == 'X')
		return (ft_putnbr_base(va_arg(args, unsigned int), type));
	else if (type == 'p')
		return (ft_print_p(va_arg(args, unsigned long), fd));
	return (0);
}
