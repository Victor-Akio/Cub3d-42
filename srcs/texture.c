/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 21:24:06 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 21:19:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					get_tex_pixel(t_all *all, int x, int y, int index)
{
	char		*color;

	color = (all->tex[index].img) + (all->tex[index].h * y *
			(all->tex[index].bpp / 8)) + (x * (all->tex[index].bpp / 8));
	if (color == 0)
		return (0);
	else
		return (*(int *)color);
}

void				draw_background(t_all *all, int x, int start, int end)
{
	int			i;

	i = 0;
	while (i < start)
	{
		my_pixel_put(&all->img, x, i, all->color_c);
		i++;
	}
	while (end < all->img.h)
	{
		my_pixel_put(&all->img, x, end, all->color_f);
		end++;
	}
}

void				get_tex(t_all *all, t_xy *line, t_xy *tex)
{
	double		wallx;
	int			line_h;

	if (all->ray.side == 0)
		wallx = all->player.map.y + all->ray.dist * all->ray.dir.y;
	else
		wallx = all->player.map.x + all->ray.dist * all->ray.dir.x;
	wallx -= floor(wallx);
	tex->x = (int)(wallx * (double)(all->tex[all->ray.wall].w));
	line_h = (int)(all->img.h / all->ray.pdist);
	line->x = (-line_h / 2 + all->img.h / 2);
	line->y = (line_h / 2 + all->img.h / 2);
}

void				draw_tex(t_all *all, int x)
{
	t_xy		line;
	int			color;
	t_xy		tex;
	int			i;

	get_tex(all, &line, &tex);
	draw_background(all, x, line.x, line.y);
	i = line.x;
	while (i < line.y)
	{
		if (i >= 0 && i < all->img.h - 1)
		{
			tex.y = all->tex[all->ray.wall].h * (i - line.x) /
				(line.y - line.x);
			color = (unsigned int)get_tex_pixel(
				all, tex.x, tex.y, all->ray.wall);
			my_pixel_put(&all->img, x, i, color);
		}
		i++;
	}
}

int					load_tex(t_all *all, char *img_addr, int i)
{
	void		*mlx;
	char		*str;

	mlx = mlx_xpm_file_to_image(all->mlx, img_addr, &all->tex[i].w,
				&all->tex[i].h);
	if (!mlx)
		error_exit("ERROR\nNo texture was loaded.");
	str = mlx_get_data_addr(mlx, &all->tex[i].bpp, &all->tex[i].line,
				&all->tex[i].endian);
	if (!str)
		error_exit("ERROR\nInvalid Textures.");
	all->tex[i].mlx = mlx;
	all->tex[i].img = str;
	return (1);
}
