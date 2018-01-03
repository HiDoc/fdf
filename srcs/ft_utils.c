/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:03:54 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/03 18:55:49 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_print_map(t_grid *grid)
{
	int		x;
	int		y;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			ft_putstr("x : ");
			ft_putnbr(grid->grid[y][x]->x);
			ft_putstr(" y : ");
			ft_putnbr(grid->grid[y][x]->y);
			ft_putstr(" z : ");
			ft_putnbr(grid->grid[y][x]->z);
			x++;
			ft_putchar('\n');
		}
		y++;
	}
}

void	ft_pix_put(t_grid *grid, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(grid->mlx,
			grid->win,
			point->x + xmod,
			point->y + ymod,
			point->color);
}

void	ft_pix_put_l(t_grid *grid, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(grid->mlx,
			grid->win,
			point->x + xmod,
			point->y + ymod,
			0x00FFFFFF);
}
