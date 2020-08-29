/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 19:19:42 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 23:45:51 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					ft_max_col(char **str)
{
	int		col;
	int		tmp;

	col = 0;
	while (*str != NULL)
	{
		tmp = ft_strlen(*str);
		col = (col > tmp) ? col : tmp;
		str++;
	}
	return (col);
}

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
