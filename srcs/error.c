/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 06:54:03 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 23:25:30 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int				error_exit(char *err)
{
	ft_putendl_fd(err, 1);
	exit(EXIT_FAILURE);
	return (1);
}

int				hook_close(t_all *all)
{
	(void)all;
	exit(EXIT_SUCCESS);
	return (0);
}

int				close_button(t_all *all)
{
	exit_game(all, EXIT_SUCCESS);
	return (0);
}
