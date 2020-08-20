/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 06:54:03 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/19 07:52:24 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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