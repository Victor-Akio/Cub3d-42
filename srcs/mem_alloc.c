/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 20:19:32 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 02:47:05 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				mem_spr(t_all *all)
{
	(void)all;
	all->ray.spr = all->map.h * all->map.w;
	all->sprites = (t_sprites *)ft_calloc(all->ray.spr, sizeof(t_sprites));
	all->ray.buffer = (double *)ft_calloc(all->img.w + 1, sizeof(double));
}
