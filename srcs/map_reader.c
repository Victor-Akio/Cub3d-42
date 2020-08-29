/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:07:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 21:08:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char				*next_word(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int					find_width(char **str, int beg, int end)
{
	int			w;
	int			i;

	w = 0;
	while (beg < end)
	{
		i = ft_strlen(str[beg]);
		if (i > w)
			w = i;
		beg++;
	}
	return (w);
}

int					ft_ischarmap(char c)
{
	if (!c || c == '\0')
		return (0);
	if (c == '0' || c == '1' || c == '2' || c == 'N' ||
			c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int					is_wall(int c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

static void			has_walls(int x, int y, int len, char **matrix)
{
	int			ptrl;

	ptrl = ft_arraylen(matrix);
	if (((y == 0 || y == ptrl - 1) || (x == 0 || x == len - 1)) &&
			(!(is_wall(matrix[y][x]))))
		error_exit("ERROR\nMap not surronded by walls.");
	if ((y > 0 && y < ptrl - 1) && (x > 0 && x < len - 1) &&
			(matrix[y][x] == '0') && ((!(ft_ischarmap(matrix[y][x - 1]))) ||
			(!(ft_ischarmap(matrix[y + 1][x]))) ||
			(!(ft_ischarmap(matrix[y][x + 1]))) ||
			(!(ft_ischarmap(matrix[y - 1][x])))))
		error_exit("ERROR\nMap not surronded by walls.");
}

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

int					set_color(char *line, int *dst)
{
	size_t		i;
	size_t		j;

	if (dst[0] != -1)
		return (-1);
	i = 0;
	j = 0;
	while (j < 3)
	{
		while (ft_isspace(line[i]))
			i++;
		if (j != 0 && line[i] == ',')
			i++;
		while (ft_isspace(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			dst[j] = 0;
		while (ft_isdigit(line[i]))
			dst[j] = (dst[j] * 10) + (line[i++] - '0');
		if (dst[j] < 0 || dst[j] > 255)
			return (-1);
		j++;
	}
	return (1);
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
