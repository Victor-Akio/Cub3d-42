/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 21:05:03 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/18 21:47:47 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			error_exit(char *err)
{
	ft_putendl_fd(err, 1);
	exit(EXIT_FAILURE);
	return (1);
}

static int			close_game(t_all *all)
{
	(void)all->mlx;
	exist(EXIT_SUCCESS);
	return (0);
}

int					main(int argc, char **argv)
{
	t_all		all;

	if (argc < 2)
		return (error_exit("ERROR: Wrong number of arguments\nPlease, insert ./cub3d [mapfile.cub]"));
	if ((all->mlx = init()) == NULL)
		return (error_exit("ERROR"))
}