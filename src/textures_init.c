/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenrach <abenrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 11:21:02 by abenrach          #+#    #+#             */
/*   Updated: 2026/08/31 11:38:46 by abenrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	assign_tex_no(t_game *game, t_player *player)
{
	player->tex_addr = game->addr_no;
	player->tex_width = game->text_no_w;
	player->tex_height = game->text_no_h;
	player->tex_bpp = game->bpp_no;
	player->tex_size_line = game->size_line_no;
}

void	assign_tex_so(t_game *game, t_player *player)
{
	player->tex_addr = game->addr_so;
	player->tex_width = game->text_so_w;
	player->tex_height = game->text_so_h;
	player->tex_bpp = game->bpp_so;
	player->tex_size_line = game->size_line_so;
}

void	assign_tex_ea(t_game *game, t_player *player)
{
	player->tex_addr = game->addr_ea;
	player->tex_width = game->text_ea_w;
	player->tex_height = game->text_ea_h;
	player->tex_bpp = game->bpp_ea;
	player->tex_size_line = game->size_line_ea;
}

void	assign_tex_we(t_game *game, t_player *player)
{
	player->tex_addr = game->addr_we;
	player->tex_width = game->text_we_w;
	player->tex_height = game->text_we_h;
	player->tex_bpp = game->bpp_we;
	player->tex_size_line = game->size_line_we;
}

void	select_texture(t_game *game, t_player *player)
{
	if (player->wall_dir == 0)
		assign_tex_no(game, player);
	else if (player->wall_dir == 1)
		assign_tex_so(game, player);
	else if (player->wall_dir == 2)
		assign_tex_ea(game, player);
	else
		assign_tex_we(game, player);
}
