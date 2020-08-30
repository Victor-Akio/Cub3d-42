/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 00:14:45 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 03:44:21 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				draw_spr_img(t_all *all, int z, int x)
{
	t_xy		i;
	t_xy		tex;
	t_xy		start;
	size_t		color;

	i.x = x - all->sprites[z].draw.x / 2;
	start.x = i.x;
	while (i.x < x + all->sprites[z].draw.x / 2 && all->sprites[z].pos.x)
	{
		tex.x = all->tex[4].w * (i.x - start.x) / all->sprites[z].draw.x;
		i.y = (all->img.h / 2) - (all->sprites[z].draw.y / 2);
		start.y = i.y;
		while (i.y < (all->img.h / 2) + (all->sprites[z].draw.y / 2) &&
			i.x >= 0 && i.x <= all->img.w)
		{
			tex.y = all->tex[4].h * (i.y - start.y) /
				all->sprites[z].draw.y;
			if (i.x > 0 && i.x < all->img.w && i.y > 0 && i.y < all->img.h &&
					all->sprites[z].pdist < all->ray.buffer[i.x])
				((color = get_tex_color(&all->tex[4], tex.x, tex.y)) &
				0x00FFFFFF) ? my_pixel_put(&all->img, i.x, i.y, color) : 0;
			i.y++;
		}
		i.x++;
	}
}

void				clear_sprites(t_all *all)
{
	int			i;

	i = 0;
	while (all->sprites[i].type != 0 && i < all->ray.spr)
	{
		all->sprites[i].pdist = 0;
		all->sprites[i].type = 0;
		all->sprites[i].pos.x = 0;
		all->sprites[i].pos.y = 0;
		i++;
	}
}

void				sort_sprites(t_all *all)
{
	int			i;
	t_sprites	tmp;

	i = 0;
	while (all->sprites[i].type != 0 && i < all->ray.spr)
	{
		if (i < all->ray.spr - 1 && all->sprites[i + 1].type != 0 &&
			all->sprites[i + 1].pdist > all->sprites[i].pdist)
		{
			tmp = all->sprites[i];
			all->sprites[i] = all->sprites[i + 1];
			all->sprites[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void				draw_spr(t_all *a)
{
	int i;
	int x;

	i = 0;
	sort_sprites(a);
	while (a->sprites[i].type != 0)
	{
		a->sprites[i].rel_pos.x = a->sprites[i].pos.x + 0.5 - a->player.map.x;
		a->sprites[i].rel_pos.y = a->sprites[i].pos.y + 0.5 - a->player.map.y;
		a->sprites[i].pdist = sqrt(pow(a->sprites[i].rel_pos.x, 2) +
											pow(a->sprites[i].rel_pos.y, 2));
		a->sprites[i].ang = ((atan2(a->sprites[i].rel_pos.x,
						a->sprites[i].rel_pos.y) / RADIAN)) -
						((atan2(a->player.dir.x, a->player.dir.y) / RADIAN));
		a->sprites[i].pdist = cos(fabs(a->sprites[i].ang) *
												RADIAN) * a->sprites[i].pdist;
		a->sprites[i].draw.y = (int)(a->img.h / a->sprites[i].pdist);
		a->sprites[i].draw.x = (a->sprites[i].draw.y *
								a->tex[4].w) / a->tex[4].h;
		x = (tan(a->sprites[i].ang * RADIAN) * a->player.dist) +
											((double)a->img.w / 2.0);
		draw_spr_img(a, i, x);
		i++;
	}
}

void				put_sprite(t_all *all, int x, int y)
{
	int			i;
	int			type;
	t_dxy		spr;

	type = all->map.map[x][y];
	i = 0;
	while (all->sprites[i].type != 0)
	{
		if (all->sprites[i].pos.x == x && all->sprites[i].pos.y == y)
			return ;
		i++;
	}
	all->sprites[i].pos.x = x;
	all->sprites[i].pos.y = y;
	all->sprites[i].type = type;
	spr.x = all->sprites[i].pos.x + 0.5 - all->player.map.x;
	spr.y = all->sprites[i].pos.y + 0.5 - all->player.map.y;
	all->sprites[i].pdist = sqrt(pow(spr.x, 2) + pow(spr.y, 2));
}
