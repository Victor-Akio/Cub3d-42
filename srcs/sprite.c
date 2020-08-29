/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 00:14:45 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/28 07:10:23 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clear_sprites(t_all *a)
{
	int i;

	i = 0;
	while (a->sprites[i].type != 0 && i < a->ray.max_sprites)
	{
		a->sprites[i].pdist = 0;
		a->sprites[i].type = 0;
		a->sprites[i].pos.x = 0;
		a->sprites[i].pos.y = 0;
		i++;
	}
}

void	sort_sprites(t_all *a)
{
	int			i;
	t_sprites	tmp;

	i = 0;
	while (a->sprites[i].type != 0 && i < a->ray.max_sprites)
	{
		if (i < a->ray.max_sprites - 1 && a->sprites[i + 1].type != 0 &&
						a->sprites[i + 1].pdist > a->sprites[i].pdist)
		{
			tmp = a->sprites[i];
			a->sprites[i] = a->sprites[i + 1];
			a->sprites[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	draw_sprite_image(t_all *a, int z, int x)
{
	t_xy			i;
	t_xy			tex;
	t_xy			start;
	unsigned int	color;

	i.x = x - a->sprites[z].draw_w / 2;
	start.x = i.x;
	while (i.x < x + a->sprites[z].draw_w / 2 && a->sprites[z].pos.x)
	{
		tex.x = a->tex[4].w * (i.x - start.x) / a->sprites[z].draw_w;
		i.y = (a->img.h / 2) - (a->sprites[z].draw_h / 2);
		start.y = i.y;
		while (i.y < (a->img.h / 2) + (a->sprites[z].draw_h / 2) &&
										i.x >= 0 && i.x <= a->img.w)
		{
			tex.y = a->tex[4].h * (i.y - start.y) /
													a->sprites[z].draw_h;
			if (i.x > 0 && i.x < a->img.w && i.y > 0 && i.y < a->img.h
								&& a->sprites[z].pdist < a->ray.buffer[i.x])
				((color = get_tex_pixel(a, tex.x, tex.y, 4)) &
				0x00FFFFFF) ? my_pixel_put(&a->img, i.x, i.y, color) : 0;
			i.y++;
		}
		i.x++;
	}
}

void				draw_spr(t_all *a)
{
	int z;
	int x;

	z = 0;
	sort_sprites(a);
	while (a->sprites[z].type != 0)
	{
		a->sprites[z].rel_pos.x = a->sprites[z].pos.x + 0.5 - a->player.pos.x;
		a->sprites[z].rel_pos.y = a->sprites[z].pos.y + 0.5 - a->player.pos.y;
		a->sprites[z].pdist = sqrt(pow(a->sprites[z].rel_pos.x, 2) +
											pow(a->sprites[z].rel_pos.y, 2));
		a->sprites[z].angle = ((atan2(a->sprites[z].rel_pos.x,
						a->sprites[z].rel_pos.y) / RADIAN)) -
						((atan2(a->player.dir.x, a->player.dir.y) / RADIAN));
		a->sprites[z].pdist = cos(fabs(a->sprites[z].angle) *
												RADIAN) * a->sprites[z].pdist;
		a->sprites[z].draw_h = (int)(a->img.h / a->sprites[z].pdist);
		a->sprites[z].draw_w = (a->sprites[z].draw_h *
								a->tex[4].w) / a->tex[4].h;
		x = (tan(a->sprites[z].angle * RADIAN) * a->player.dist) +
											((double)a->img.w / 2.0);
		draw_sprite_image(a, z, x);
		z++;
	}
}


void	put_sprite(t_all *all, int x, int y)
{
	int		i;
	int		type;
	t_xy	s;

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
	s.x = all->sprites[i].pos.x + 0.5 - all->player.pos.x;
	s.y = all->sprites[i].pos.y + 0.5 - all->player.pos.y;
	all->sprites[i].pdist = sqrt(pow(s.x, 2) + pow(s.y, 2));
}