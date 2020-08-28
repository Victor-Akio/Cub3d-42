/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 05:14:57 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/28 08:13:45 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void				mv_up(t_all *all)
{
	if (all->map.map[(int)(all->player.map.x + all->player.dir.x *
			(all->walk * 4))][(int)(all->player.map.y)] == '0')
		all->player.map.x += all->player.dir.x * all->walk;
	if (all->map.map[(int)(all->player.map.x)][(int)(all->player.map.y +
			all->player.dir.y * (all->walk * 4))] == '0')
		all->player.map.y += all->player.dir.y * all->walk;
}

void				mv_down(t_all *all)
{
	if (all->map.map[(int)(all->player.map.x - all->player.dir.x *
			(all->walk * 3))][(int)(all->player.map.y)] == '0')
		all->player.map.x -= all->player.dir.x * all->walk;
	if (all->map.map[(int)(all->player.map.x)][(int)(all->player.map.y -
			all->player.dir.y * (all->walk * 3))] == '0')
		all->player.map.y -= all->player.dir.y * all->walk;
}

void				mv_left(t_all * all)
{
	rotate_horizontal(-90, all->player.dir, &all->player.dir);
	mv_up(all);
	rotate_horizontal(90, all->player.dir, &all->player.dir);
}

void				mv_right(t_all * all)
{
	rotate_horizontal(90, all->player.dir, &all->player.dir);
	mv_up(all);
	rotate_horizontal(-90, all->player.dir, &all->player.dir);
}