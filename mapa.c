/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:57:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/20 22:51:20 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (i < all->img.tile_size)
	{
		j = 0;
		while (j < all->img.tile_size)
		{
			//my_pixel_put(win, i + x, j + y, color);
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
	all->img.tile_size = ft_tile_size(all);
	all->color_f = create_trgb(0, 252, 238, 195);
	all->color_c = create_trgb(0, 151, 142, 117);
	while (i < ft_arraylen(all->map.map))
	{
		j = 0;
		tiley = i * all->img.tile_size;
		while (all->map.map[i][j] && j < ft_max_col(all->map.map))
		{
			tilex = j * all->img.tile_size;
			if (all->map.map[i][j] && all->map.map[i][j] == '1')
				rect(all, tilex, tiley, all->map.color_w);
			else if (all->map.map[i][j] && (all->map.map[i][j] != '1' && 
						all->map.map[i][j] != ' '))
				rect(all, tilex, tiley, all->map.color_f2d);
			else if (all->map.map[i][j] && (all->map.map[i][j] == 'N' || all->map.map[i][j] == 'E' ||
						all->map.map[i][j] == 'S' ||all->map.map[i][j] == 'W'))
				player_pos(all, i, j);
			j++;
		}
		i++;
	}
	render_player(all);
}