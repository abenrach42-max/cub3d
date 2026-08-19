/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcissoko <hcissoko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 15:09:09 by hcissoko          #+#    #+#             */
/*   Updated: 2026/08/19 15:09:09 by hcissoko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		return (close_win(data));
	if (keycode == 119)
		data->keys.w = 1;
	if (keycode == 115)
		data->keys.s = 1;
	if (keycode == 100)
		data->keys.d = 1;
	if (keycode == 97)
		data->keys.a = 1;
	if (keycode == 65361)
		data->keys.right = 1;
	if (keycode == 65363)
		data->keys.left = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 0;
	if (keycode == 115)
		data->keys.s = 0;
	if (keycode == 100)
		data->keys.d = 0;
	if (keycode == 97)
		data->keys.a = 0;
	if (keycode == 65361)
		data->keys.right = 0;
	if (keycode == 65363)
		data->keys.left = 0;
	return (0);
}
