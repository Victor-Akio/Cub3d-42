/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 23:23:13 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/20 21:26:01 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	circle(t_all *all, int x, int y, int r)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < all->map.h)
	{
		j = 0;
		while (j < all->map.w)
		{
			if ((((i-x)*(i-x)) + ((j-y)*(j-y))) <= (r*r))
				//my_pixel_put(all->win, i, j, 0xC31433);
				mlx_pixel_put(all->mlx, all->win, i, j, 0xC31433);
			j++;
		}
		i++;
	}
}

void				render_player(t_all *all)
{
	circle(all, all->map.w / 2, all->map.h / 2, 3);
}

void				rotate_horizontal(double ang, t_xy in, t_xy *out)
{
	t_xy		tmp;
	double		radian;

	radian = ang * (PI / 180);
	tmp.x = in.x;
	tmp.y = in.y;
	out->x = (cos(radian) * tmp.x) + (sin(radian) * tmp.y);
	out->y = (-sin(radian) * tmp.x) + (cos(radian) * tmp.y);
}

int					player_pos(t_all *all, int x, int y, char c)
{
	if (all->player.pos.x != 0 || all->player.pos.y != 0)
	{
		error_exit("ERROR\nSomething went wrong with the player.");
		return (0);
	}
	all->player.pos.x = x + 0.5;
	all->player.pos.y = (all->map.h - 1) - y + 0.5;
	if (c == 'N')
		rotate_horizontal(NO, all->player.dir, &all->player.dir);
	else if (c == 'S')
		rotate_horizontal(SO, all->player.dir, &all->player.dir);
	else if (c == 'w')
		rotate_horizontal(WE, all->player.dir, &all->player.dir);
	else if (c == 'E')
		rotate_horizontal(EA, all->player.dir, &all->player.dir);
	return (1);
}
