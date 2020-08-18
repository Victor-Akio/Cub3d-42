/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 21:18:11 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/18 21:44:20 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_all				*init(void)
{
	t_all *all;
	
	if ((all = ft_memalloc(sizeof(t_all))) == NULL)
		return (NULL);
	if ((all->mlx = mlx_init()) == NULL ||
					(all->win = mlx_new_window(all->mlx, WIN_W,
					WIN_H, GAME_TITLE)) == NULL ||
					(all->img = creat_img(all, WIN_W, WIN_H)) == NULL)
		return (mlx_destroy(all));
	return (all);
}