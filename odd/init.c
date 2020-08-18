/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 22:12:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/15 22:58:51 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_init2(t_all *all)
{
	if (all->color_c == -1)
		all->color_c = 0x16a7f5;
	if (all->color_f == -1)
		all->color_f = 0x797c7d;
	if (all->win.w == 0)
		all->win.w = 640;
	if (all->win.h == 0)
		all->win.h = 480;
		return (1);
}

void				ft_init(t_all *all)
{
	all->map.h = 0;
	all->map.w = 0;
	all->map.map = 0;
	all->win.img = NULL;
	all->win.win = NULL;
	all->win.addr = NULL;
	all->win.w = 0;
	all->win.h = 0;
	all->win.fov = 0;
	all->rotation = 5;
	all->walk = 0.5;
	all->color_c = -1;
	all->color_f = -1;
	all->player.pos.x = 0;
	all->player.pos.y = 0;
	all->player.dir.x = 0;
	all->player.dir.y = 0;
	all->tex = NULL;
}

void				window_init(t_win *win, t_map *map)
{
	win->win = mlx_new_window(win->mlx, win->w, win->h, GAME_TITLE);
	win->img = mlx_new_image(win->mlx, win->w, win->h);
	win->addr = mlx_get_data_addr(win->img, &(win->bpp), &(win->line), &(win->endian));
	map_gen(win, map);
	//mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
}