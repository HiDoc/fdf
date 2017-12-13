/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:20:19 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 14:19:00 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include <math.h>

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	char		*color;
}				t_point;
typedef struct	s_grid
{
	t_point		***grid;
	int			size_x;
	int			size_y;
}				t_grid;
t_point			*ft_new_point(int x, int y, int z);
void			ft_del_point(t_point *point);
t_grid			*ft_new_grid(t_point ***tab, int size_x, int size_y);
void			ft_del_grid(t_grid *grid);
void			ft_ini_grid(t_grid *grid, int y);
int				real_y(t_grid *grid, int x, int y);
int				ft_parse_line(int y, t_grid *grid, char *str, int filled);
int				ft_parse_file(int fd, t_grid *grid, int sized);
int				ft_pythagore(int a, int b);
t_grid			*ft_read(char *file);
int				ft_draw(char *file);
#endif
