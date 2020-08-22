/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 03:28:49 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/22 01:34:57 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char				**ft_realloc(char **str)
{
	int			i;
	int			j;
	char		**tmp;

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

char				**read_file(char *filename)
{
	char		**str;
	char		*line;
	int			i;
	int			fd;
	int			ret;

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
	close (fd);
	return (str);
}

void				file_init(t_file *file)
{
	int			i;

	file->data = NULL;
	i = 0;
	while (i < 5)
	{
		file->keys[i] = NULL;
		i++;
	}
}

int					load_file(t_all *all, char *filename)
{
	file_init(&all->file);
	if (!(all->file.data = read_file(filename)) || (!(read_map(all, all->file.data))))
		return (0);
	return (1);
}