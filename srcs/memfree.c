/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 02:48:16 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/28 07:02:29 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				free_win(t_all *all)
{
	if (all->img.img && all->mlx)
		mlx_destroy_image(all->mlx, all->img.img);
	if (all->win && all->mlx)
		mlx_destroy_window(all->mlx, all->win);
}

void				free_tex(t_all *all)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		if (all->tex)
		{
			if (all->tex[i].mlx)
				mlx_destroy_image(all->mlx, all->tex[i].mlx);
		}
		i++;
	}
	if (all->tex)
		free(all->tex);
}

void				free_ray(t_all *all)
{
	if (all->ray.buffer == NULL)
		free(all->ray.buffer);
	all->ray.buffer = NULL;
}

void				free_map(t_all *all)
{
	int			i;
	t_map		*map;


	i = 0;
	map = &all->map;
	while (i < map->h && map->map[i])
	{
		if (map->map[i])
			free(map->map[i]);
		i++;
	}
	map->map = NULL;
}
