/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:57:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/22 12:30:32 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				my_pixel_put(t_img *win, int x, int y, int color)
{
	char		*dst;

	dst = win->addr + (y * win->line + x * (win->bpp / 8));
	*(unsigned int *)dst = color;
}

void				rect(t_all *all, int x, int y, int color)
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
			//my_pixel_put(all->win, i + x, j + y, color);
			mlx_pixel_put(all->mlx, all->win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void				map_gen(t_all *all)
{
	int			i;
	int			j;
	int			tilex;
	int			tiley;
	
	i = 0;
	all->map.color_w = create_trgb(0, 252, 238, 195);
	all->map.color_f2d = create_trgb(0, 151, 142, 117);
	while (i < ft_arraylen(all->map.map))
	{
		j = 0;
		tiley = i * TILE_SIZE;
		while (all->map.map[i][j] && j < ft_max_col(all->map.map))
		{
			tilex = j * TILE_SIZE;
			if (all->map.map[i][j] && all->map.map[i][j] == '1')
				rect(all, tilex, tiley, all->map.color_w);
			else if (all->map.map[i][j] && (all->map.map[i][j] != '1' && 
						all->map.map[i][j] != ' '))
				rect(all, tilex, tiley, all->map.color_f2d);
			if (all->map.map[i][j] && (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'E' ||
				all->map.map[i][j] == 'S' ||all->map.map[i][j] == 'W'))
			{
				all->player.pos.x = tilex + TILE_SIZE / 2;
				all->player.pos.y = tiley + TILE_SIZE / 2;
				all->player.way = all->map.map[i][j];
				all->player.map.x = i;
				all->player.map.y = j;
			}
			j++;
		}
		i++;
	}	
}