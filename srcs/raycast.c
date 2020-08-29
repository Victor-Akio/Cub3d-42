/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:55:40 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 21:17:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				calc_pdist(t_all *all)
{
	if (all->ray.side == 0)
		all->ray.dist = (all->ray.pos.x - all->player.map.x +
				(1.0 - all->ray.step.x) / 2.0) / all->ray.dir.x;
	else
		all->ray.dist = (all->ray.pos.y - all->player.map.y +
				(1.0 - all->ray.step.y) / 2.0) / all->ray.dir.y;
	all->ray.pdist = cos(fabs(all->ray.ang) * RADIAN) * all->ray.dist;
}

void				delta_dangle(t_all *all)
{
	int			hit;

	hit = 0;
	while (hit == 0)
	{
		if (all->ray.ab_dist.x <= all->ray.ab_dist.y)
		{
			all->ray.ab_dist.x += all->ray.delta_dist.x;
			all->ray.pos.x += all->ray.step.x;
			all->ray.side = 0;
			all->ray.wall = all->ray.step.x == 1 ? 2 : 3;
		}
		else
		{
			all->ray.ab_dist.y += all->ray.delta_dist.y;
			all->ray.pos.y += all->ray.step.y;
			all->ray.side = 1;
			all->ray.wall = all->ray.step.y == 1 ? 1 : 0;
		}
		// if (all->map.map[(int)ray->pos.x][(int)ray->pos.y] > 1)
		// 	put_sprite(all, (int)ray->pos.x, (int)ray->pos.y);
		if (all->map.map[(int)all->ray.pos.x][(int)all->ray.pos.y] == '1')
			hit = 1;
	}
}

void				calc_step_dir(t_ray *ray)
{
	ray->step.x = 1;
	if (ray->dir.x >= 0)
		ray->ab_dist.x = (floor(ray->pos.x) + 1.0 - ray->pos.x) * ray->delta_dist.x;
	else
	{
		ray->step.x = -1;
		ray->ab_dist.x = (ray->pos.x - floor(ray->pos.x)) * ray->delta_dist.x;
	}
	ray->step.y = 1;
	if (ray->dir.y >= 0)
		ray->ab_dist.y = (floor(ray->pos.y) + 1.0 - ray->pos.y) * ray->delta_dist.y;
	else
	{
		ray->step.y = -1;
		ray->ab_dist.y = (ray->pos.y - floor(ray->pos.y)) * ray->delta_dist.y;
	}
	ray->pos.x = floor(ray->pos.x);
	ray->pos.y = floor(ray->pos.y);
}

void				calc_rays(t_all *all)
{
	int			i;

	i = 0;
//	clear_sprites(all);
	while (i < all->img.w)
	{
		all->ray.ang = (atan2(i - all->img.w / 2, all->player.dist) / RADIAN);
		rotate_horizontal(all->ray.ang, all->player.dir, &all->ray.dir);
		all->ray.delta_dist.x = fabs(1.0 / all->ray.dir.x);
		all->ray.delta_dist.y = fabs(1.0 / all->ray.dir.y);
		all->ray.pos = all->player.map;
		calc_step_dir(&all->ray);
		delta_dangle(all);
		calc_pdist(all);
		draw_tex(all, i);
		all->ray.buffer[i] = all->ray.pdist;
		i++;
	}
//	draw_spr(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
}
