/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:03:54 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/06 19:32:33 by fmadura          ###   ########.fr       */
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
			point->x + xmod + (fdf->x_win / 2 - fdf->x_end / 2),
			point->y + ymod + abs(fdf->y_start) + fdf->y_win / 2,
			point->color);
}

void	ft_pix_put(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
	int color = point->color - ymod;
	if (ymod > 0 && point->color == 0x00BB0000)
		color = 0x00BB0000;
	mlx_pixel_put(fdf->mlx,
			fdf->win,
			point->x + xmod + (fdf->x_win / 2 - fdf->x_end / 2),
			point->y + ymod + abs(fdf->y_start) + fdf->y_win / 2,
			color);
}
void	ft_pix_put_l(t_fdf *fdf, t_point *point, int xmod, int ymod)
{
//	mlx_pixel_put(fdf->mlx,
//			fdf->win,
//			point->x + xmod + (fdf->x_win / 2 - fdf->x_end / 2),
//			point->y + ymod + abs(fdf->y_start),
//			0x00000000);
//			;
	(void)fdf;
	(void)point;
	(void)xmod;
	(void)ymod;

}
