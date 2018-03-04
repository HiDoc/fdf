/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:53:21 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/04 12:24:59 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_pix_put_color(t_fdf *fdf, int xmod, int ymod, int color)
{
	mlx_pixel_put(fdf->mlx,
			fdf->win,
			xmod + fdf->x_center,
			ymod + fdf->y_center,
			color);
}
void	ft_pix_put_flat(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(fdf->mlx,
			fdf->win,
			point->x + xmod + fdf->x_center,
			point->y + ymod + fdf->y_center,
			point->color);
}
