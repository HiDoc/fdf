/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:29:19 by fmadura           #+#    #+#             */
/*   Updated: 2018/02/15 22:51:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define RED 0x00010000
#define GRN 0x00000100
#define BLU 0x000000FF
#define BSC 0x00000001

void	ft_del_point(t_point *point)
{
	free(point);
}

void	ft_map_point(int (f)(t_fdf *fdf, t_point *, int, int),
		t_fdf *fdf, char coord)
{
	int		y;
	int		x;
	int		replace;
	t_point	*point;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			point = fdf->grid[y][x];
			replace = f(fdf, point, x, y);
			if (coord == 'x')
				point->x = replace;
			else if (coord == 'y')
				point->y = replace;
			else if (coord == 'z')
				point->z = replace;
			else if (coord == 'c')
				point->color = replace;
			x++;
		}
		y++;
	}
}

int		ft_colr(t_fdf *fdf, t_point *point, int x, int y)
{
	int		rgb;

	(void)x;
	(void)y;
	(void)fdf;
	rgb =  BLU + ABS(point->z * BSC * 20);
	return (rgb);
}

int		ft_posy(t_fdf *fdf, t_point *point, int x, int y)
{
	(void)x;
	return ((y - point->z) * fdf->res);
}

int		ft_posx(t_fdf *fdf, t_point *point, int x, int y)
{
	(void)point;
	return ((x * fdf->res) + (y * fdf->res));}
