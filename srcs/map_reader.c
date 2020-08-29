/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:07:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 00:25:42 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				ft_cub_valid_map(char **matrix)
{
	t_xy		xy;
	t_xy		len;

	xy.x = 0;
	xy.y = 0;
	len.y = ft_arraylen(matrix);
	while (xy.y < len.y - 1)
	{
		len.x = ft_strlen(matrix[xy.y]);
		while (xy.x < len.x)
		{
			has_walls(xy.x, xy.y, len.x, matrix);
			xy.x++;
		}
		xy.x = 0;
		xy.y++;
	}
}

int					read_map(t_all *all, char **matrix)
{
	char	*tmp;

	while (matrix)
	{
		tmp = next_word(*matrix);
		if (ft_isdigit(*tmp))
		{
			ft_cub_valid_map(matrix);
			break ;
		}
		*matrix = next_word(*matrix);
		if (**matrix == 'R')
		{
			(*matrix)++;
			*matrix = next_word(*matrix);
			all->map.w = ft_atoi(*matrix);
			*matrix = next_word((*matrix) + ft_intlen(all->map.w));
			all->map.h = ft_atoi(*matrix);
		}
		else if (ft_strncmp(*matrix, "NO", 2) == 0)
			all->file.keys[3] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "SO", 2) == 0)
			all->file.keys[2] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "WE", 2) == 0)
			all->file.keys[0] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "EA", 2) == 0)
			all->file.keys[1] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "S", 1) == 0)
			all->file.keys[4] = next_word(++(*matrix));
		else if (ft_strncmp(*matrix, "F", 1) == 0)
			set_color(++(*matrix), &(all->rgb_f[0]));
		else if (ft_strncmp(*matrix, "C", 1) == 0)
			set_color(++(*matrix), &(all->rgb_c[0]));
		matrix++;
	}
	all->color_f = create_trgb(0, all->rgb_f[0], all->rgb_f[1], all->rgb_f[2]);
	all->color_c = create_trgb(0, all->rgb_c[0], all->rgb_c[1], all->rgb_c[2]);
	all->map.map = matrix;
	all->img.h = all->map.h;
	all->img.w = all->map.w;
	return (1);
}
