/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 03:57:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/15 07:31:11 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				my_pixel_put(t_win *win, int x, int y, int color)
{
	char		*dst;

	dst = win->addr + (y * win->line + x * (win->bpp / 8));
	*(unsigned int *)dst = color;
}

void				rect(t_win *win, int x, int y, int color, t_map *map)
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
			//my_pixel_put(win, i + x, j + y, color);
			mlx_pixel_put(win->mlx, win->win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void				map_gen(t_win *win, t_map *map)
{
	int i;
	int j;
	int	size;
	int worldmap[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	i = 0;
	size = TILE_SIZE * 0.3;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			rect(win, j * size, i * size, worldmap[i][j] == 1 ? 0x978E75 : 0xFCEEC3, map);
			j++;
		}
		i++;

	}
}