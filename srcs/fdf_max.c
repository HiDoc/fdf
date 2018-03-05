/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:23 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 17:34:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf		*fdf_max_y(t_fdf *fdf)
{
	int x;
	int y;
	int max;
	int min;

	y = 0;
	x = 0;
	max = 0;
	min = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			if (fdf->grid[y][x]->y < min)
				min = fdf->grid[y][x]->y;
			if (fdf->grid[y][x]->y > max)
				max = fdf->grid[y][x]->y;
			x++;
		}
		y++;
	}
	fdf->y_start = min;
	fdf->y_end = max;
	return (fdf);
}

t_fdf		*fdf_max_x(t_fdf *fdf)
{
	int count;
	int max;

	count = 0;
	max = 0;
	while (count < fdf->size_y)
	{
		if (fdf->size_x[count] + count > max)
			max = fdf->size_x[count] + count;
		count++;
	}
	fdf->x_start = 0;
	fdf->x_end = max * fdf->res;
	return (fdf);
}

t_fdf		*fdf_max_z(t_fdf *fdf)
{
	int x;
	int y;
	int max;
	int min;

	y = 0;
	x = 0;
	max = fdf->size_x[0] ? fdf->grid[0][0]->z : 0;
	min = fdf->size_x[0] ? fdf->grid[0][0]->z : 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			if (fdf->grid[y][x]->z < min)
				min = fdf->grid[y][x]->z;
			if (fdf->grid[y][x]->z > max)
				max = fdf->grid[y][x]->z;
			x++;
		}
		y++;
	}
	fdf->z_min = min;
	fdf->z_max = max;
	return (fdf);
}
