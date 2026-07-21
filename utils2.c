/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:53:45 by abenrach          #+#    #+#             */
/*   Updated: 2026/07/19 20:39:10 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_tab(char **tab, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

int     find_max_tab(char **tab)
{
    int     i;
    int     j;
    int     max;
    
    i = 0;
    max = 0;
    while (tab[i] != NULL)
    {
        j = 0;
        while (tab[i][j])
            j++;
        if (max < j)
            max = j;
        i++;
    }
    return (max);
}

void    free_game(t_game *game)
{
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    if (game->img_ea)
        mlx_destroy_image(game->mlx, game->img_ea);
    if (game->img_we)
        mlx_destroy_image(game->mlx, game->img_we);
    if (game->img_so)
        mlx_destroy_image(game->mlx, game->img_so);
    if (game->img_no)
        mlx_destroy_image(game->mlx, game->img_no);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    free(game);
}

void    free_all(t_data *data)
{
    if (data->player)
        free(data->player);
    if (data->game)
        free_game(data->game);
    if (data->tab)
        free_tab(data->tab, tab_len(data->tab));
    if (data->ceiling_color)
        free(data->ceiling_color);
    if (data->floor_color)
        free(data->floor_color);
    if (data->ea_path)
        free(data->ea_path);
    if (data->we_path)
        free(data->we_path);
    if (data->so_path)
        free(data->so_path);
    if (data->no_path)
        free(data->no_path);
    free(data);
}

