/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:20:19 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/28 15:18:26 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define RES 20
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;
typedef struct	s_grid
{
	t_point		***grid;
	int			size_x;
	int			size_y;
	void		*mlx;
	void		*win;
}				t_grid;
int				ft_distance(t_point *p1, t_point *p2);
void			ft_del_point(t_point *point);
void			ft_map_point(int (f)(t_point *, int, int), t_grid *g, char c);
int				ft_posx(t_point *point, int x, int y);
int				ft_colr(t_point *point, int x, int y);
int				ft_posy(t_point *point, int x, int y);
t_grid			*ft_add_mlx(t_grid *grid);
void			ft_del_grid(t_grid *grid);
t_grid			*ft_ini_grid(t_grid *grid, int y);
t_grid			*ft_map_grid(t_grid *grid);
void			ft_res_grid(t_grid *grid);
int				real_y(t_grid *grid, int x, int y);
int				ft_parse_line(int y, t_grid *grid, char *str, int filled);
int				ft_parse_file(int fd, t_grid *grid, int sized);
int				ft_pythagore(int a, int b);
t_grid			*ft_read(char *file);
int				ft_draw(char *file);
void			ft_print_map(t_grid *grid);
#endif
