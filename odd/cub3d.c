/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:29:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/14 23:20:50 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_error_number;

int					exit_game(t_all *all, int ret)
{
	free_map(all);
	free_file(all);
	exit(ret);
}

int					launch_game(t_all *all)
{
	ft_init(all);
	if (!(ft_init2(all)) || !(load_file(all, all->file.filename)))
		return (0);
	window_init(&all->win, &all->map);
	return (1);
}

int					check_args(t_all *all, int argc, char **argv)
{
	if (argc <= 0)
		g_error_number = ERR_INVALID_ARG;
	else if (argc == 1)
	{
		all->file.filename = "./mapa.cub";
		return (1);
	}
	else if (ft_strlen(argv[1]) <= 4 || ft_strncmp(argv[1] +
				(ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
		g_error_number = ERR_INVALID_NAME;
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
		g_error_number = ERR_INVALID_SEC_ARG;
	if (g_error_number)
		return (0);
	all->file.filename = argv[1];
	return (argc -1);
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				args;

	if (!(all.win.mlx = mlx_init()))
	{
		g_error_number = ERR_MLX;
		ft_error(&all, FALSE);
	}
	args = check_args(&all, argc, argv);
	if (!(args))
		ft_error(&all, FALSE);
	if (!(launch_game(&all)))
		ft_error(&all, TRUE);
	if (args == 2)
		exit_game(&all, 0);
	mlx_loop(all.win.mlx);
	return (0);
}