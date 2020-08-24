/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 01:55:40 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/24 04:03:14 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					calculate_rays(t_all *all)
{
	int			i;

	i = 0;
	//clear_sprites(all);
	while (i < all->img.w)
	{
		all->ray.ang = (atan2(i - all->img.w / 2, all->player.dist) / RADIAN);
		rotate_horizontal(all->ray.ang, all->player.dir, &all->ray.dir);
		all->ray.dir_dist.x = fabs(1.0 / all->ray.dir.x);
		all->ray.dir_dist.y = fabs(1.0 / all->ray.dir.y);
		all->ray.pos = all->player.pos;
		//calc_step_dir(&all->ray);
		//perform_dda(all, &all->ray);
		//calc_ndist(all);
		//draw_tex(all, i);
		all->ray.buffer[i] = all->ray.n_dist;
		i++;
	}
	//draw_spr(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 10, 10);
}