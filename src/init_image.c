/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 11:40:34 by abenrach          #+#    #+#             */
/*   Updated: 2026/08/31 11:46:28 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_img_no(t_data *data, t_game *game)
{
	game->img_no = mlx_xpm_file_to_image(game->mlx, data->no_path,
			&game->text_no_w, &game->text_no_h);
	if (!game->img_no)
		return (print_error("Image north init fail"), 1);
	game->addr_no = mlx_get_data_addr(game->img_no, &game->bpp_no,
			&game->size_line_no, &game->endian_no);
	if (!game->addr_no)
		return (print_error("Get addr north fail"), 1);
	return (0);
}

int	init_img_so(t_data *data, t_game *game)
{
	game->img_so = mlx_xpm_file_to_image(game->mlx, data->so_path,
			&game->text_so_w, &game->text_so_h);
	if (!game->img_so)
		return (print_error("Image south init fail"), 1);
	game->addr_so = mlx_get_data_addr(game->img_so, &game->bpp_so,
			&game->size_line_so, &game->endian_so);
	if (!game->addr_so)
		return (print_error("Get addr south fail"), 1);
	return (0);
}

int	init_img_ea(t_data *data, t_game *game)
{
	game->img_ea = mlx_xpm_file_to_image(game->mlx, data->ea_path,
			&game->text_ea_w, &game->text_ea_h);
	if (!game->img_ea)
		return (print_error("Image east init fail"), 1);
	game->addr_ea = mlx_get_data_addr(game->img_ea, &game->bpp_ea,
			&game->size_line_ea, &game->endian_ea);
	if (!game->addr_ea)
		return (print_error("Get addr east fail"), 1);
	return (0);
}

int	init_img_we(t_data *data, t_game *game)
{
	game->img_we = mlx_xpm_file_to_image(game->mlx, data->we_path,
			&game->text_we_w, &game->text_we_h);
	if (!game->img_we)
		return (print_error("Image weast init fail"), 1);
	game->addr_we = mlx_get_data_addr(game->img_we, &game->bpp_we,
			&game->size_line_we, &game->endian_we);
	if (!game->addr_we)
		return (print_error("Get addr weast fail"), 1);
	return (0);
}
