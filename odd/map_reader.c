/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:07:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/14 21:24:10 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int					read_map(t_all *all)
{
	char		**cub;
	int			i;
	t_xy		xy;

	i = 0;
	cub = all->file.data;
	while (cub[i] && (cub[i][0] != ' ' && !ft_isdigit(cub[i][0])))
		i++;
	xy.y = i;
	while (cub[i] && (cub[i][0] == ' ' || ft_isdigit(cub[i][0])))
		i++;
	xy.y = i;
	all->map.w = find_width(cub, xy.x, xy.y);
	all->map.h = xy.y - xy.x;
	all->map.map = (int **)ft_calloc(all->map.w, sizeof(int *));
	return (1);
}