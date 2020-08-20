/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 03:28:49 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/20 21:28:01 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	i;

	file_init(&all->file);
	if (!(all->file.data = read_file(filename)) || (!(read_map(all, all->file.data))))
		return (0);
	i = 0;
	while (all->file.data[i])
	{
		printf("%s\n", all->file.data[i++]);
	}
	printf("%d\n", all->map.w);
	printf("%d\n", all->map.h);
	return (1);
}