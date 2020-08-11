/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:04:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/11 06:29:04 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct			s_mlx
{
	int				mlx;
	int				img;
}						t_mlx;

typedef struct			s_win
{
	int				win;
	int				h;
	int				w;
}						t_win;


typedef struct			s_all
{
	t_mlx			mlx;
	t_win			win;
}						t_all;

#ifndef CUB3D_ERRORS_H
# define CUB3D_ERRORS_H

# define ERR_MAP_INVALIDARG 2
# define ERR_FILE_INVALIDARG 3
# define ERR_MAP_UNKNOWN_CHAR 4
# define ERR_MAP_LINE_SPACES 5
# define ERR_MAP_INVALID 6
# define ERR_PLAYER_POS_ALRSET 10
# define ERR_PLAYER_POS_NOTSET 11
# define ERR_TEXTURE_NOLOAD 15
# define ERR_TEXTURE_INVALID 16
# define ERR_FILE_PROBLEM 20
# define ERR_INVALID_SEC_ARG 22
# define ERR_FILE_INVALIDFNAME 25
# define ERR_MLX 30

extern int g_error_number;

#endif

#endif