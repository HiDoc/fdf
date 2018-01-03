/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:29:19 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/03 18:54:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define RED 0x00BB0000
#define GRN 0x0000FF00
#define BLU 0x000000FF

void	ft_del_point(t_point *point)
{
	free(point);
}

void	ft_map_point(int (f)(t_point *, int, int), t_grid *grid, char coord)
{
	int		y;
	int		x;
	int		replace;
	t_point	*point;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			point = grid->grid[y][x];
			replace = f(point, x, y);
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

int		ft_colr(t_point *point, int x, int y)
{
	int		rgb;

	(void)x;
	(void)y;
	rgb = RED + point->z * 25;
	return (rgb);
}

int		ft_posy(t_point *point, int x, int y)
{
	(void)x;
	return ((y - point->z) * RES + 600);
}

int		ft_posx(t_point *point, int x, int y)
{
	(void)point;
	return ((x * RES + 200) + (y * RES));
}
