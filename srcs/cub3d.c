/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:29:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 20:08:18 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		g_error_number;

void				game_validatescreen(t_all *all)
{
	int			width;
	int		height;

	mlx_get_screen_size(all->mlx, &width, &height);
	if (all->img.w > width)
		all->img.w = width;
	if (all->img.h > height)
		all->img.h = height;
}

int					exit_game(t_all *all, int ret)
{
	if (all->ray.buffer)
		free(all->ray.buffer);
	free_map(all);
	free_ray(all);
	free_win(all);
	free_tex(all);
	if (all->sprite)
		free(all->sprite);
	exit(ret);
}

int					launch_game(t_all *all)
{
	ft_init(all);
	if (!(ft_init2(all)) || !(load_file(all, all->file.filename)) ||
			!(tex_init(all)))
		return (0);
	mem_spr(all);
	window_init(all, &all->img);
	return (1);
}

int					check_args(t_all *all, int argc, char **argv)
{
	if (argc <= 1)
		return (error_exit("ERROR\nNot enough arguments\nUSE: ./cub3d [mapfile.cub]"));
	else if (argc == 2)
	{
		if (ft_strlen(argv[1]) <= 4 || ft_strncmp(argv[1] +
				(ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
			return (error_exit("ERROR\nInvalid Map Name]"));
		all->file.filename = argv[1];
		return (argc -1);
	}
	else if (argc == 3)
	{
		if (ft_strncmp(argv[1], "--save", 6) != 0)
			return (error_exit("ERROR\nInvalid third argument.\nUSE: --save"));	
		if (ft_strlen(argv[2]) <= 4 || ft_strncmp(argv[2] +
				(ft_strlen(argv[2]) - 4), ".cub", 4) != 0)
			return (error_exit("ERROR\nInvalid Map Name."));
		all->file.filename = argv[2];
		return (argc -1);
	}
	return (error_exit("ERROR\nInvalid arguments."));
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				args;

	if (!(all.mlx = mlx_init()))
		return (error_exit("ERROR\nMLX could not start properly"));
	args = check_args(&all, argc, argv);
	if (!(args))
		hook_close(&all);
	if (!(launch_game(&all)))
		exit_game(&all, EXIT_SUCCESS);
	calc_rays(&all);
	set_hooks(&all);
	if (args == 2 && !(convert_bmp(&all)))
		exit_game(&all, EXIT_SUCCESS);
	if (args == 2)
		exit_game(&all, EXIT_FAILURE);
	mlx_loop(all.mlx);
	return (0);
}