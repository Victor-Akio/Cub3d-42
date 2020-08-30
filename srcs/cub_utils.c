/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 23:36:35 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 04:17:33 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					cub_str_ismap(char **cub, int id)
{
	size_t		i;

	i = 0;
	while (cub[id][i] != '\0' && ft_strchr("012NSWE \t\n\v\f\r", cub[id][i]))
		i++;
	if (cub[id][i] == '\0')
		return (1);
	return (0);
}

int					cub_str_isspace(char *line)
{
	size_t		i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int					get_tex_color(t_tex *tex, int x, int y)
{
	if (x >= 0 && x < tex->w && y >= 0 && y < tex->h)
		return (*(int *)(tex->img + (4 * tex->w * y) + (4 * x)));
	return (0);
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

void				has_walls(int x, int y, int len, char **matrix)
{
	int			ptrl;

	ptrl = ft_arraylen(matrix);
	if (((y == 0 || y == ptrl - 1) || (x == 0 || x == len - 1)) &&
			(!(ft_iswall(matrix[y][x]))))
		error_exit("ERROR\nMap not surronded by walls.");
	if ((y > 0 && y < ptrl - 1) && (x > 0 && x < len - 1) &&
			(matrix[y][x] == '0') && ((!(ft_ischarmap(matrix[y][x - 1]))) ||
			(!(ft_ischarmap(matrix[y + 1][x]))) ||
			(!(ft_ischarmap(matrix[y][x + 1]))) ||
			(!(ft_ischarmap(matrix[y - 1][x])))))
		error_exit("ERROR\nMap not surronded by walls.");
}
