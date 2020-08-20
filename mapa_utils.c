/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 19:19:42 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/20 19:26:01 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					ft_max_col(char	**str)
{
	int		col;
	int		tmp;

	col = 0;
	while (*str != NULL)
	{
		tmp= ft_strlen(*str);
		col = (col > tmp) ? col : tmp;
		str++;
	}
	return (col);
}

int					ft_tile_size(t_all *all)
{
	if (ft_arraylen(all->map.map) > ft_max_col(all->map.map))
		return (all->map.h / ft_arraylen(all->map.map));
	else
		return (all->map.w / ft_max_col(all->map.map));
}