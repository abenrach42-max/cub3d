/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:31:59 by hcissoko          #+#    #+#             */
/*   Updated: 2026/05/11 21:32:33 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strs_size(char **strs)
{
	size_t	i;

	if (!strs)
		return (0);
	i = 0;
	while (strs[i])
		i++;
	return (i);
}

void	ft_strsfree(char **strs, size_t i)
{
	if (!strs)
		return ;
	while (0 < i)
	{
		i--;
		free(strs[i]);
	}
	free(strs);
}
