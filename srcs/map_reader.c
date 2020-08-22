/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:07:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/22 12:28:40 by vminomiy         ###   ########.fr       */
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

int					check_border(t_all *all, t_xy pos)
{
	t_xy		xy;
	t_xy		up;
	t_xy		turn;

	turn.x = 0;
	turn.y = 0;
	while (turn.x <= 3)
	{
		xy = pos;
		up.x = (turn.x % 2 == 0) ? 1 : 0;
		turn.y = (turn.x >= 2) ? -1 : 1;
		while (xy.x >= 0 && xy.x < all->map.w && xy.y >= 0 && xy.y < all->map.h)
		{
			if (all->map.map[xy.x][xy.y] == -1 || (((xy.x == 0 || xy.x == all->map.w - 1) || (xy.y == 0 || xy.y == all->map.h - 1)) && all->map.map[xy.x][xy.y] != 1))
				return (0);
			else if (all->map.map[xy.x][xy.y] == 1)
				break ;
			xy.x += (up.x * turn.y);
			xy.y += (!(up.x) * turn.y);
		}
		turn.x++;
	}
	return (1);
}

int					ft_cub_valid_map(t_all *all, char **matrix)
{
	t_xy		pos;
	int			c;

	pos.x = 0;
	all->map.map = matrix;
	while (pos.x < all->map.w)
	{
		pos.y = 0;
		while (pos.y < all->map.h)
		{
			c = all->map.map[pos.x][pos.y];
			if (c > 1 || c == 0)
				if (!(check_border(all, pos)))
					return (0);
			pos.y++;
		}
		pos.x++;
	}
	return (1);
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
		while(ft_isdigit(line[i]))
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
			ft_cub_valid_map(all, matrix);
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
			all->file.keys[0] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "SO", 2) == 0)
			all->file.keys[1] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "WE", 2) == 0)
			all->file.keys[2] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "EA", 2) == 0)
			all->file.keys[3] = next_word(*matrix += 2);
		else if (ft_strncmp(*matrix, "S", 1) == 0)
			all->file.keys[4] = next_word(++(*matrix));
		else if (ft_strncmp(*matrix, "F" , 1) == 0)
			set_color(++(*matrix), &(all->floor[0]));
		else if (ft_strncmp(*matrix, "C" , 1) == 0)
			set_color(++(*matrix), &(all->celling[0]));
		matrix++;
	}
	return (1);
}