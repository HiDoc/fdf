/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:20:19 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/10 17:11:53 by fmadura          ###   ########.fr       */
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
	int			z;
	char		*color;
}				t_point;
typedef struct	s_grid
{
	int			**grid;
	int			size_x;
	int			size_y;
}				t_grid;
t_point			*ft_new_point(int z);
t_grid			*ft_new_grid(int **tab, int size_x, int size_y);
void			ft_del_grid(t_grid *grid);
int				ft_parse_line(int y, t_grid *grid, char *str, int filled);
int				ft_parse_file(int fd, t_grid *grid, int sized);
int				ft_pythagore(int a, int b);
t_grid			*ft_read(char *file);
int				ft_draw(char *file);
#endif
