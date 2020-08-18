/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:04:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/18 21:45:47 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

# define EXIT_SUCCESS 1
# define EXIT_FAILURE 0
# define GAME_TITLE "Cub3d"
# define TILE_SIZE 32

# define WIN_W = 1280
# define WIN_H = 720

typedef struct			s_xy
{
	double			x;
	double			y;
}						t_xy;

typedef struct			s_player
{
	t_xy			pos;
	t_xy			dir;
	double			hip;
}						t_player;

typedef struct			s_sprite
{
	int				type;
	t_xy			pos;
}						t_sprite;

typedef struct			s_ray
{
	t_xy			pos;
	t_xy			dir;
}						t_ray;

typedef struct			s_tex
{
	char			*img;
	int				w;
	int				h;
	int				bpp;
	int				line;
	int				endian;
}						t_tex;

typedef struct			s_map
{
	int				**map;
	int				w;
	int				h;
}						t_map;

typedef struct			s_img
{
	void			*img;
	char			*addr;
	int				h;
	int				w;
	int				bpp;
	int				line;
	int				endian;
	double			fov;
}						t_img;

typedef struct			s_file
{
	char			*filename;
	char			**data;
	char			*keys[5];
}						t_file;

typedef struct			s_all
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_file			file;
	t_img			img;
	t_ray			ray;
	t_player		player;
	t_tex			*tex;
	t_sprite		*sprite;
	double			rotation;
	double			walk;
	int				color_c;
	int				color_f;
}						t_all;

static int			error_exit(char *err);
static int			close_game(t_all *all);

t_all				*init(void);

#endif