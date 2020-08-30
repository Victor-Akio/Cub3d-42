/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 21:07:26 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 04:58:45 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					set_resolution(char *line, t_all *all)
{
	if (all->map.w != -1 || all->map.h != -1)
		return (-1);
	line = next_word(line);
	all->map.w = ft_atoi(line);
	line = next_word((line) + ft_intlen(all->map.w));
	all->map.h = ft_atoi(line);
	if (all->map.w < 1 || all->map.h < 1)
		return (-1);
	return (1);
}

int					set_path(char **line, char *nxword)
{
	if (*line != NULL)
		return (-1);
	*line = nxword;
	return (1);
}

int					valid_map(char **cub, t_all *all)
{
	size_t		i;
	size_t		j;
	int			ply;

	ply = 0;
	i = 0;
	while (cub[i])
	{
		j = 0;
		while (cub[i][j] && ft_strchr("012NSWE \t\n\v\f\r", cub[i][j]))
		{
			if (cub[i][j] == 'N' || cub[i][j] == 'S' || cub[i][j] == 'E'
				|| cub[i][j] == 'W')
				ply++;
			j++;
		}
		i++;
	}
	if (ply != 1)
		error_exit("ERROR\n Something wrong with player");
	ft_cub_valid_map(cub);
	all->map.map = cub;
	return (1);
}

int					cub_handler(t_all *all, char **mat, int i)
{
	if (ft_strncmp(mat[i], "R", 1) == 0)
		return (set_resolution(&mat[i][1], all));
	else if (ft_strncmp(mat[i], "NO", 2) == 0)
		return (set_path(&(all->file.keys[3]), next_word(mat[i] += 2)));
	else if (ft_strncmp(mat[i], "SO", 2) == 0)
		return (set_path(&(all->file.keys[2]), next_word(mat[i] += 2)));
	else if (ft_strncmp(mat[i], "WE", 2) == 0)
		return (set_path(&(all->file.keys[0]), next_word(mat[i] += 2)));
	else if (ft_strncmp(mat[i], "EA", 2) == 0)
		return (set_path(&(all->file.keys[1]), next_word(mat[i] += 2)));
	else if (ft_strncmp(mat[i], "S", 1) == 0)
		return (set_path(&(all->file.keys[4]), next_word(++(mat[i]))));
	else if (ft_strncmp(mat[i], "F", 1) == 0)
		return (set_color(++(mat[i]), &(all->rgb_f[0])));
	else if (ft_strncmp(mat[i], "C", 1) == 0)
		return (set_color(++(mat[i]), &(all->rgb_c[0])));
	else if (cub_str_isspace(mat[i]))
		return (0);
	else if (cub_str_ismap(mat, i))
		return (valid_map(mat + i, all));
	return (-1);
}

int					garead_map(t_all *all, char **mat)
{
	int			status;
	int			tmp;
	int			i;

	i = 0;
	tmp = -1;
	status = 0;
	while (status < 9)
	{
		if (!mat[i])
			error_exit("ERROR\nInvalid Map structure.");
		tmp = cub_handler(all, mat, i++);
		status += tmp;
		if (tmp < 0 || (all->map.map != NULL && status < 9))
			error_exit("ERROR\nInvalid map arguments.");
	}
	all->color_f = create_trgb(0, all->rgb_f[0], all->rgb_f[1], all->rgb_f[2]);
	all->color_c = create_trgb(0, all->rgb_c[0], all->rgb_c[1], all->rgb_c[2]);
	all->img.h = all->map.h;
	all->img.w = all->map.w;
	return (1);
}
