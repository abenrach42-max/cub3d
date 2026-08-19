/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:37:35 by hcissoko          #+#    #+#             */
/*   Updated: 2025/11/12 19:43:19 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	size_t	i;
	size_t	j;

	len_little = 0;
	i = 0;
	while (little[len_little])
		len_little++;
	if (len_little == 0)
		return ((char *) big);
	while (i < len && big[i])
	{
		j = 0;
		while ((i + j) < len && j < len_little && little[j] == big[i + j])
		{
			j++;
			if (j == len_little)
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}
