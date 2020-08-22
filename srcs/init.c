/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 22:12:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/22 20:12:31 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					ft_init2(t_all *all)
{
	if (all->img.w == 0)
		all->img.w = 800;
	if (all->img.h == 0)
		all->img.h = 800;
	return (1);
}

void				ft_init(t_all *all)
{
	all->map.h = 0;
	all->map.w = 0;
	all->map.map = 0;
	all->img.img = NULL;
	all->win = NULL;
	all->img.addr = NULL;
	all->img.w = 0;
	all->img.h = 0;
	all->img.fov = 0;
	all->rotation = 5;
	all->walk = 0.5;
	all->color_c[0] = -1;
	all->color_f[0] = -1;
	all->player.pos.x = 0;
	all->player.pos.y = 0;
	all->player.dir.x = 0;
	all->player.dir.y = 0;
	all->tex = NULL;
}

void				window_init(t_all *all, t_img *win)
{
	all->win = mlx_new_window(all->mlx, win->w, win->h, GAME_TITLE);
	win->img = mlx_new_image(all->mlx, win->w, win->h);
	win->addr = mlx_get_data_addr(win->img, &(win->bits_per_pixel),
		&(win->line_length), &(win->endian));
	map_gen(all);
	player_pos(all);
	//mlx_put_image_to_window(all->mlx, all->win, win->img, 10, 10);
}