/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:04:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/20 22:20:57 by vminomiy         ###   ########.fr       */
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

# define PI 3.14159265
# define RADIAN 0.0174533
# define NO 0
# define EA 90
# define SO 180
# define WE 270

# define GAME_TITLE "Cub3d"

typedef struct			s_dxy
{
	double			x;
	double			y;
}						t_dxy;

typedef struct			s_xy
{
	int				x;
	int				y;
}						t_xy;

typedef struct			s_player
{
	t_xy			pos;
	t_xy			dir;
	char			**face[4];
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

typedef struct			s_cast
{
	int				mx;
	int				my;
	t_xy			s;
	t_xy			d;
	int				stepx;
	int				stepy;
	float			wall;
}						t_cast;

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
	char			**map;
	int				w;
	int				h;
	int				color_w;
	int				color_f2d;
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
	int				fov;
	int				tile_size;
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

int					error_exit(char *err);
int					hook_close(t_all *all);
int					exit_game(t_all *all, int ret);
int					load_file(t_all *all, char *filename);
void				file_init(t_file *file);
char				**ft_realloc(char **str);
int					read_map(t_all *all, char **matrix);
int					find_width(char **str, int beg, int end);
int					ft_init2(t_all *all);
void				ft_init(t_all *all);
void				window_init(t_all *all, t_img *win, t_map *map);
int					load_file(t_all *all, char *filename);
void				file_init(t_file *file);
char				**read_file(char *filename);
void				free_map(t_all *all);
void				free_file(t_all *all);
void				map_gen(t_all *all);
int					ft_max_col(char	**str);
int					ft_tile_size(t_all *all);
void				render_player(t_all *all);
void				my_pixel_put(t_img *win, int x, int y, int color);

#endif