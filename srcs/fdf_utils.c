/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:41:41 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/22 17:10:26 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	fdf_labs(long param)
{
	return (param > 0 ? param : -param);
}

int		fdf_no_value(t_fdf *fdf)
{
	int		count;
	int		has_value;

	count = 0;
	has_value = 0;
	if (!(fdf->size_y))
		return (0);
	while (count < fdf->size_y)
	{
		if (fdf->size_x[count] > 0)
			has_value++;
		count++;
	}
	return (has_value);
}

void	fdf_pix_put_color(t_fdf *fdf, int xmod, int ymod, int color)
{
	mlx_pixel_put(fdf->mlx,
			fdf->win,
			xmod + fdf->x_center + fdf->x_center_mod,
			ymod + fdf->y_center + fdf->y_center_mod,
			color);
}

void	fdf_pix_put_flat(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(fdf->mlx,
			fdf->win,
			point->x + xmod + fdf->x_center + fdf->x_center_mod,
			point->y + ymod + fdf->y_center + fdf->y_center_mod,
			point->color);
}
