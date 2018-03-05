/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:39:58 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 13:40:00 by fmadura          ###   ########.fr       */
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

t_fdf		*ft_ini_fdf(t_fdf *fdf, int res)
{
	fdf->res = res;
	ft_max_z(fdf);
	ft_map_fdf(fdf);
	ft_max_x(fdf);
	ft_max_y(fdf);
	fdf->x_win = 800;
	fdf->y_win = 800;
	fdf->x_center = fdf->x_win / 2 - fdf->x_end / 2;
	fdf->y_center = abs(fdf->y_start) + fdf->y_win / 2
	- (fdf->y_end - fdf->y_start) / 2;
	return (fdf);
}
