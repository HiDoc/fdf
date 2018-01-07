/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:45:05 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/07 14:38:23 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf		*ft_map_fdf(t_fdf *fdf)
{
	ft_map_point(&ft_colr, fdf, 'c');
	ft_map_point(&ft_posx, fdf, 'x');
	ft_map_point(&ft_posy, fdf, 'y');
	return (fdf);
}

t_fdf		*ft_add_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->x_win, fdf->y_win, "FDF");
	return (fdf);
}

t_fdf		*ft_max_y(t_fdf *fdf)
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

t_fdf		*ft_max_x(t_fdf *fdf)
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
	printf("%d\n",fdf->x_end);
	return (fdf);
}

t_fdf		*ft_ini_fdf(t_fdf *fdf)
{
	fdf->res = 20;
	fdf->y_start = 0;
	fdf->x_win = 800;
	fdf->y_win = 800;
	fdf->x_end = 0;
	ft_map_fdf(fdf);
	ft_max_x(fdf);
	ft_max_y(fdf);
	fdf->x_center = fdf->x_win / 2 - fdf->x_end / 2;
	fdf->y_center = abs(fdf->y_start) + fdf->y_win / 2 - (fdf->y_end - fdf->y_start) / 2;
	printf("%d\n",fdf->x_end);
	printf("%d\n",fdf->y_end);
	printf("%d\n",fdf->y_start);
	ft_add_mlx(fdf);
	return (fdf);
}
