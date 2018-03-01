/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 13:05:57 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/01 19:39:57 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
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
	int			res;
	int			x_start;
	int			y_start;
	int			x_end;
	int			y_end;
	int			x_win;
	int			y_win;
	int			x_center;
	int			y_center;
	void		*mlx;
	void		*win;
}				t_fdf;

void			ft_map_point(int (f)(t_fdf *, t_point *, int, int), t_fdf *g, char c);
int				ft_colr(t_fdf *fdf, t_point *point, int x, int y);
int				ft_posx(t_fdf *fdf, t_point *point, int x, int y);
int				ft_posy(t_fdf *fdf, t_point *point, int x, int y);

void			ft_del_point(t_point *point);
void			ft_del_grid(t_fdf *fdf);
void			ft_res_grid(t_fdf *fdf);

int				ft_parse_file(int fd, t_fdf *fdf, int sized);
int				ft_parse_line(int y, t_fdf *fdf, char *str, int filled);

int				real_y(t_fdf *fdf, int x, int y);

int				ft_coef(t_fdf *fdf, t_point *a, t_point *b);

t_fdf			*ft_add_mlx(t_fdf *fdf);
t_fdf			*ft_ini_fdf(t_fdf *fdfi, int res);
t_fdf			*ft_ini_line(t_fdf *fdf, int y);

t_fdf			*ft_max_y(t_fdf *fdf);
t_fdf			*ft_max_x(t_fdf *fdf);
t_fdf			*ft_map_fdf(t_fdf *fdf);

void			ft_res_fdf(t_fdf *fdf);

void			ft_pix_put_flat(t_fdf *fdf, t_point *point, int xmod, int ymod);
void			ft_pix_put_color(t_fdf *fdf, int xmod, int ymod, int color);

int				ft_pythagore(int a, int b);

t_fdf			*ft_read(char *file);
int				ft_draw(char *file);
#endif
