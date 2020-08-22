/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 23:23:13 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/22 03:18:08 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		get_tile(t_all *all, int x, int y)
{
	if (x < 0 || y < 0 || x > all->map.w - 1 || y > all->map.h - 1)
		return (0);
	return (all->map.map[y][x]);
}

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
				mlx_pixel_put(all->mlx, all->win, i, j, 0xC31433);
			j++;
		}
		i++;
	}
}

void				render_player(t_all *all)
{
	int			x;
	int			y;
	int			f;

	y = 0;
	f = 0;
	while (y < all->map.h)
	{
		x = 0;
		while (x < all->map.w)
		{
			if (!(f = get_tile(all, x, y)))
				break ;
			x++;
		}
		if (!f)
			break ;
		y++;
	}
	all->player.dir.x = x + 0.5;
	all->player.dir.y = y + 0.5;
	circle(all, x, y, 6);
}

void				rotate_horizontal(double ang, t_dxy in, t_dxy *out)
{
	t_xy		tmp;
	double		radian;

	radian = ang * (PI / 180);
	tmp.x = in.x;
	tmp.y = in.y;
	out->x = (cos(radian) * tmp.x) + (sin(radian) * tmp.y);
	out->y = (-sin(radian) * tmp.x) + (cos(radian) * tmp.y);
}

int					player_pos(t_all *all, int x, int y)
{
	if (all->player.pos.x != 0 || all->player.pos.y != 0)
	{
		error_exit("ERROR\nSomething went wrong with the player.");
		return (0);
	}
	all->player.pos.x = x + 0.5;
	all->player.pos.y = (all->map.h - 1) - y + 0.5;
	if (all->map.map[x][y] == 'N')
		rotate_horizontal(NV, all->player.dir, &all->player.dir);
	else if (all->map.map[x][y] == 'S')
		rotate_horizontal(SV, all->player.dir, &all->player.dir);
	else if (all->map.map[x][y] == 'w')
		rotate_horizontal(WV, all->player.dir, &all->player.dir);
	else if (all->map.map[x][y] == 'E')
		rotate_horizontal(EV, all->player.dir, &all->player.dir);
	render_player(all);
	return (1);
}

void				put_player(t_all *all)
{
	int			i;
	int			j;
	int			tilex;
	int			tiley;

	i = 0;
	while (i < ft_arraylen(all->map.map))
	{
		j = 0;
		tiley = i * TILE_SIZE;
		while (all->map.map[i][j] && j < ft_max_col(all->map.map))
		{
			tilex = j * TILE_SIZE;
			if (all->map.map[i][j] && (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'E' ||
				all->map.map[i][j] == 'S' ||all->map.map[i][j] == 'W'))
				player_pos(all, (tiley + TILE_SIZE / 2), (tilex + TILE_SIZE / 2));
			j++;
		}
		i++;
	}
}