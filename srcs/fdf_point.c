/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:32 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 13:41:33 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int		ft_posy(t_fdf *fdf, t_point *point, int x, int y)
{
	(void)x;
	return ((y - point->z) * fdf->res);
}

int		ft_posx(t_fdf *fdf, t_point *point, int x, int y)
{
	(void)point;
	return ((x * fdf->res) + (y * fdf->res));
}
