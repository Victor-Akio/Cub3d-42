/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 05:14:33 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 23:25:11 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					get_keypress(int key, t_all *all)
{
	if (key == KEY_ESC)
		close_button(all);
	if (key == KEY_LEFT)
		rotate_horizontal(-all->rotation, all->player.dir, &all->player.dir);
	if (key == KEY_RIGHT)
		rotate_horizontal(all->rotation, all->player.dir, &all->player.dir);
	if (key == KEY_W)
		mv_up(all);
	if (key == KEY_S)
		mv_down(all);
	if (key == KEY_A)
		mv_left(all);
	if (key == KEY_D)
		mv_right(all);
	calc_rays(all);
	return (1);
}

int					game_loop(t_all *all)
{
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
	return (1);
}

void				set_hooks(t_all *all)
{
	mlx_hook(all->win, X11_KEYPRESS, 1L << 0, get_keypress, all);
	mlx_hook(all->win, X11_DESTROY, 0, close_button, all);
	mlx_hook(all->win, 33, 0, close_button, all);
	mlx_hook(all->win, 9, 1L << 21, game_loop, all);
}
