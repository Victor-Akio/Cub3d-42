/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:57:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 23:41:01 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char		*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	rect(t_all *all, int x, int y, int color)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_pixel_put(&(all->minimap), x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	map_gen(t_all *all)
{
	int			i;
	int			j;

	i = 0;
	while (i < ft_arraylen(all->map.map))
	{
		j = 0;
		while (all->map.map[i][j] && j < ft_max_col(all->map.map))
		{
			if (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'E' ||
				all->map.map[i][j] == 'S' || all->map.map[i][j] == 'W')
			{
				all->player.pos.x = (j * TILE_SIZE) + TILE_SIZE / 2;
				all->player.pos.y = (i * TILE_SIZE) + TILE_SIZE / 2;
				all->player.way = all->map.map[i][j];
				all->player.map.x = i + 0.5;
				all->player.map.y = j + 0.5;
			}
			j++;
		}
		i++;
	}
}
