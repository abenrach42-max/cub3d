/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 19:35:51 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/03 19:40:43 by abenrach         ###   ########.fr       */
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
    printf("%s\n", data->ea_path);
    printf("%s\n", data->we_path);
    printf("%s\n", data->so_path);
    printf("%s\n", data->no_path);
    printf("%s\n", data->floor_color);
    printf("%s\n", data->ceiling_color);
    free_all_data(data);
    return (0);
}
