/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:07:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/22 01:36:40 by vminomiy         ###   ########.fr       */
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

void	ft_cub_valid_map(t_all *all, char **matrix)
{
	all->map.map = matrix; // validar mapa
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
		matrix++;
	}
	return (1);
}