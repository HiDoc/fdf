/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:39:58 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/08 13:10:50 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		fdf_clear_fdf(t_fdf *fdf)
{
	if (fdf->grid)
		fdf_del_grid(fdf);
	if (fdf->size_x)
		free(fdf->size_x);
	if (fdf)
		free(fdf);
}

t_fdf		*fdf_map_fdf(t_fdf *fdf)
{
	fdf_map_point(&fdf_colr, fdf, 'c');
	fdf_map_point(&fdf_posx, fdf, 'x');
	fdf_map_point(&fdf_posy, fdf, 'y');
	return (fdf);
}

t_fdf		*fdf_add_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, fdf->x_win, fdf->y_win, "FDF");
	return (fdf);
}

t_fdf		*fdf_ini_fdf(t_fdf *fdf, int res)
{
	if (!fdf->color)
		fdf->color = 0xFFFFFF;
	if (!fdf->color2)
		fdf->color2 = 0x00FF00;
	fdf->res = res;
	fdf_max_z(fdf);
	fdf_map_fdf(fdf);
	fdf_max_x(fdf);
	fdf_max_y(fdf);
	fdf->x_win = 800;
	fdf->y_win = 800;
	fdf->x_center = fdf->x_win / 2 - fdf->x_end / 2;
	fdf->y_center = abs(fdf->y_start) + fdf->y_win / 2
	- (fdf->y_end - fdf->y_start) / 2;
	return (fdf);
}
