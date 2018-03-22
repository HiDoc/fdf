/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:05:57 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/22 17:36:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libftprintf.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <errno.h>
# include <fcntl.h>

void			mlx_int_loop_once(void);

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct	s_fdf
{
	t_point		***grid;
	int			*size_x;
	int			size_y;
	int			coef;
	float		res;
	float		resbase;
	long		x_start;
	long		y_start;
	long		x_end;
	long		y_end;
	long		x_win;
	long		y_win;
	long		x_center;
	long		y_center;
	int			x_center_mod;
	int			y_center_mod;
	long		z_max;
	long		z_min;
	int			rand;
	int			color;
	int			color2;
	void		*mlx;
	void		*win;
}				t_fdf;

void			fdf_map_point(int (f)(t_fdf *, t_point *, int, int),
				t_fdf *g, char c);
int				fdf_colr(t_fdf *fdf, t_point *point, int x, int y);
int				fdf_posx(t_fdf *fdf, t_point *point, int x, int y);
int				fdf_posy(t_fdf *fdf, t_point *point, int x, int y);
int				fdf_posz(t_fdf *fdf, t_point *point, int x, int y);
int				fdf_rncg(t_fdf *fdf, t_point *point, int x, int y);

void			fdf_del_point(t_point *point);
void			fdf_del_grid(t_fdf *fdf);
void			fdf_res_grid(t_fdf *fdf);

int				real_y(t_fdf *fdf, int x, int y);
int				fdf_coef(t_fdf *fdf, t_point *a, t_point *b);

t_fdf			*fdf_add_mlx(t_fdf *fdf);
t_fdf			*fdf_ini_fdf(t_fdf *fdf, float res);
t_fdf			*fdf_ini_line(t_fdf *fdf, int y);

t_fdf			*fdf_max_z(t_fdf *fdf);
t_fdf			*fdf_max_y(t_fdf *fdf);
t_fdf			*fdf_max_x(t_fdf *fdf);
t_fdf			*fdf_map_fdf(t_fdf *fdf);

void			fdf_res_fdf(t_fdf *fdf);
void			fdf_clear_fdf(t_fdf *fdf);

void			fdf_pix_put_flat(t_fdf *fdf, t_point *point,
				int xmod, int ymod);

void			fdf_pix_put_color(t_fdf *fdf, int xmod, int ymod, int color);

int				fdf_color_mixer(int color1, int color2, float mix);
int				fdf_pythagore(int a, int b);
long			fdf_labs(long param);
int				fdf_rand(int seed, int increment, int modulus, int multiplier);
int				fdf_random(int seed);
int				key_hook(int keycode, void *param);
int				key_zoom(int keycode, t_fdf *fdf);
int				key_color(int keycode, t_fdf *fdf);

t_fdf			*fdf_read(char *file);

int				fdf_draw(char *file);
int				fdf_draw_lines(t_fdf *fdf);
int				fdf_draw_lines_temp(t_fdf *fdf);

void			*fdf_error(int code, t_fdf *fdf);
void			fdf_usage(void);
void			fdf_keycode(void);
int				fdf_no_value(t_fdf *fdf);
#endif
