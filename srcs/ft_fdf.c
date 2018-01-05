/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:45:05 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/05 17:11:35 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*ft_map_fdf(t_fdf *fdf)
{
	ft_map_point(&ft_colr, fdf, 'c');
	ft_map_point(&ft_posx, fdf, 'x');
	ft_map_point(&ft_posy, fdf, 'y');
	return (fdf);
}

t_fdf	*ft_add_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, "FDF");
	return (fdf);
}

t_fdf	*ft_max_fdf(t_fdf *fdf)
{
/*	int		y;
	int		x;
	int		ymax;
	int		xmax;

	ymax = 0;
	xmax = 0;
	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			if (abs(xmax) < abs(fdf->grid[y][x]->x))
				xmax = fdf->grid[y][x]->x;
			if (abs(ymax) < abs(fdf->grid[y][x]->y))
				ymax = fdf->grid[y][x]->y;
			x++;
		}
		y++;
	}
	fdf->x_end = xmax;
	fdf->y_end = ymax;*/
	return (fdf);
}

t_fdf	*ft_ini_fdf(t_fdf *fdf)
{
	fdf->res = 20;
	ft_max_fdf(fdf);
	ft_map_fdf(fdf);
	ft_add_mlx(fdf);
	return (fdf);
}
