/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 03:28:49 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 03:49:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char **ft_realloc(char **str)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	if (!str)
		str = (char **)ft_calloc(1, sizeof(char *));
	tmp = str;
	j = ft_arraylen(str);
	str = (char **)ft_calloc((j + 2), sizeof(char *));
	while (i < j)
	{
		str[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (str);
}

char **read_file(char *filename)
{
	char **str;
	char *line;
	int i;
	int fd;
	int ret;

	i = 0;
	str = NULL;
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		error_exit("ERROR\nCould not open file.");
		return (NULL);
	}
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		str = ft_realloc(str);
		str[i] = line;
		i++;
		if (ret == 0)
			break;
	}
	close(fd);
	return (str);
}

void file_init(t_file *file)
{
	int i;

	file->data = NULL;
	i = 0;
	while (i < 5)
	{
		file->keys[i] = NULL;
		i++;
	}
}

int set_resolution(char *line, t_all *all)
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

int	set_path(char **line, char *nxword)
{
	if (*line != NULL)
		return (-1);
	*line = nxword;
	return (1);
}

int	cub_str_ismap(char **cub, int id)
{
	size_t	i;

	i = 0;
	while (cub[id][i] != '\0' && ft_strchr("012NSWE \t\n\v\f\r", cub[id][i]))
		i++;
	if (cub[id][i] == '\0')
		return (1);
	return (0);
}

int	cub_str_isspace(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	valid_map(char **cub, t_all *all)
{
	size_t	i;
	size_t	j;
	int		ply;

	ply = 0;
	i = 0;
	while(cub[i])
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


int cub_handler(t_all *all, char **mat, int i)
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

int garead_map(t_all *all, char **mat)
{
	int status;
	int tmp;
	int i;

	i = 0;
	tmp = -1;
	status = 0;
	while (status < 9)
	{
		if (!mat[i])
			return (0);
		tmp = cub_handler(all, mat, i++);
		status += tmp;
		if (tmp < 0 || (all->map.map != NULL && status < 9))
			return (0);
	}
	all->color_f = create_trgb(0, all->rgb_f[0], all->rgb_f[1], all->rgb_f[2]);
	all->color_c = create_trgb(0, all->rgb_c[0], all->rgb_c[1], all->rgb_c[2]);
	all->img.h = all->map.h;
	all->img.w = all->map.w;
	return (1);
}

int load_file(t_all *all, char *filename)
{
	file_init(&all->file);
	if (!(all->file.data = read_file(filename)) ||
		!(garead_map(all, all->file.data)))
		return (0);
	return (1);
}
