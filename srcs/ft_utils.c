/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 17:03:54 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 17:09:11 by fmadura          ###   ########.fr       */
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
