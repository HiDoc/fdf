/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:03:54 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/08 15:31:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_map(t_fdf *fdf)
{
	int		x;
	int		y;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			ft_putstr("x : ");
			ft_putnbr(fdf->grid[y][x]->x);
			ft_putstr(" y : ");
			ft_putnbr(fdf->grid[y][x]->y);
			ft_putstr(" z : ");
			ft_putnbr(fdf->grid[y][x]->z);
			x++;
			ft_putchar('\n');
		}
		y++;
	}
}

void	ft_pix_put_flat(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(fdf->mlx,
			fdf->win,
			point->x + xmod + fdf->x_center,
			point->y + ymod + fdf->y_center,
			point->color);
}

void	ft_pix_put(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
	int color;

	color = point->color - ymod;
	if (ymod > 0 && point->color == 0x00BB0000)
		color = 0x00BB0000;
	mlx_pixel_put(
			fdf->mlx,
			fdf->win,
			point->x + xmod + fdf->x_center,
			point->y + ymod + fdf->y_center,
			color);
}

void	ft_pix_put_l(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
	(void)fdf;
	(void)point;
	(void)xmod;
	(void)ymod;
}
