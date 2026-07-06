/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enemxa <enemxa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:35:51 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/06 21:45:48 by enemxa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
    t_data  *data;

	if (ac != 2)
	    return (1);
    data = init_data(av[1]);
    if (!data)
        return (puts("Error"), 1);
    puts("reussi");
    for (int i = 0; data->tab[i] != NULL; i++)
        printf("%s", data->tab[i]);
    free_all_data(data);
    return (0);
}
