/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 19:52:58 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 21:58:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int			data_bmp(t_img *img, int fd)
{
	int			i;

	i = img->w * img->h - 1;
	while (i >= 0)
	{
		write(fd, &img->addr[i * img->bits_per_pixel / 8], 4);
		i--;
	}
	return (1);
}

static void			bmp_pixel_put(t_img *img, int line, int *e, int f)
{
	int			save;
	int			k;

	k = 3;
	while (k >= 0)
	{
		save = img->addr[*e + (line * img->line_length)];
		img->addr[*e + (line * img->line_length)] = img->addr
			[f - k + (line * img->line_length - 1)];
		img->addr[f - k + (line * img->line_length - 1)] = save;
		k--;
		*e = *e + 1;
	}
}

static int			mir_vert(t_img *img)
{
	int			line;
	int			e;
	int			f;

	line = 0;
	while (line < img->h)
	{
		e = 0;
		f = img->line_length;
		while (e < f && e != f)
		{
			bmp_pixel_put(img, line, &e, f);
			f -= 4;
		}
		line++;
	}
	return (1);
}

static int			bmp_header(t_img *img, int fd)
{
	int			size;
	int			plane;
	int			x;

	size = 40;
	plane = 1;
	write(fd, &size, 4);
	write(fd, &img->w, 4);
	write(fd, &img->h, 4);
	write(fd, &plane, 2);
	write(fd, &img->bits_per_pixel, 2);
	x = 0;
	while (x < 28)
	{
		write(fd, "\0", 1);
		x++;
	}
	return (1);
}

int					convert_bmp(t_all *all)
{
	int			fd;
	int			size;
	int			start;

	fd = open("cub3d.bmp", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR |
			S_IRGRP | S_IROTH);
	size = 14 + 40 + 4 + (all->img.w * all->img.h) * 4;
	start = 14 + 40 + 4;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &start, 4);
	bmp_header(&all->img, fd);
	mir_vert(&all->img);
	data_bmp(&all->img, fd);
	close(fd);
	return (1);
}
