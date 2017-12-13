/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:29:19 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 17:55:52 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*ft_new_point(int x, int y, int z)
{
	t_point	*point;

	if ((point = (t_point *)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->color = ft_strdup("0x00FFFFFF");
	return (point->color != NULL ? point : NULL);
}

void	ft_del_point(t_point *point)
{
	free(point);
}

void	ft_map_point(int (f)(t_point *, int, int), t_grid *grid, char coord)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			if (coord == 'x')
				(grid->grid[y][x])->x = f(grid->grid[y][x], x, y);
			else if (coord == 'y')
				(grid->grid[y][x])->y = f(grid->grid[y][x], x, y);
			else if (coord == 'z')
				(grid->grid[y][x])->z = f(grid->grid[y][x], x, y);
			x++;
		}
		y++;
	}
}

int		ft_posy(t_point *point, int x, int y)
{
	(void) x;
	return ((y - point->z) * RES + 400);
}

int		ft_posx(t_point *point, int x, int y)
{
	(void) point;
	return ((x * RES + 200) + (y * RES));
}
