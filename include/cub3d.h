/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:04:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 10:30:49 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "sys/stat.h"

# define PI 3.14159265
# define RADIAN 0.0174533
# define NV 270
# define EV 180
# define SV 90
# define WV 0

# define KEY_ESC 65307
# define KEY_A 97
# define KEY_D 100
# define KEY_W 119
# define KEY_S 115
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define X11_KEYPRESS 2
# define X11_DESTROY 17

# define TILE_SIZE 20
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
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			map;
	char			way;
	char			**face[4];
	double			dist;
}						t_player;

typedef struct			s_sprite
{
	int				type;
	t_xy			pos;
}						t_sprite;

typedef struct			s_ray
{
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			delta_dist;
	t_dxy			ab_dist;
	t_dxy			step;
	double			ang;
	double			size;
	double			dist;
	double			pdist;
	double			*buffer;
	int				side;
	int				wall;
	int				spr;
}						t_ray;

typedef struct			s_tex
{
	char			*img;
	void			*mlx;
	int				w;
	int				h;
	int				bpp;
	int				line;
	int				endian;
	int				set;
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
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				fov;
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
	t_img			minimap;
	t_ray			ray;
	t_player		player;
	t_tex			*tex;
	t_sprite		*sprite;
	double			rotation;
	double			walk;
	int				rgb_f[3];
	int				rgb_c[3];
	int				color_f;
	int				color_c;
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
void				window_init(t_all *all, t_img *win);
int					load_file(t_all *all, char *filename);
void				file_init(t_file *file);
char				**read_file(char *filename);
void				map_gen(t_all *all);
int					ft_max_col(char	**str);
int					ft_tile_size(t_all *all);
void				render_player(t_all *all);
void				my_pixel_put(t_img *img, int x, int y, int color);
int					player_pos(t_all *all);
void				set_hooks(t_all *all);
void				mv_up(t_all *all);
void				mv_down(t_all *all);
void				mv_right(t_all *all);
void				mv_left(t_all *all);
int					close_button(t_all *all);
void				rotate_horizontal(double ang, t_dxy in, t_dxy *out);
void				calc_rays(t_all *all);
int					tex_init(t_all *all);
int					load_tex(t_all *all, char *img_addr, int i);
void				draw_tex(t_all *all, int x);
int					create_trgb(int t, int r, int g, int b);
void				mem_spr(t_all *all);
int					convert_bmp(t_all *all);
void				game_validatescreen(t_all *all);

void				free_win(t_all *all);
void				free_tex(t_all *all);
void				free_ray(t_all *all);
void				free_map(t_all *all);

#endif
