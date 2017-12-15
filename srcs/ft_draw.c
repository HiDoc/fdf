/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/15 15:08:49 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_pix_put(t_grid *grid, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(grid->mlx,
			grid->win,
			point->x + xmod,
			point->y + ymod,
			point->color);
}

static void	ft_draw_lines_sub(t_grid *grid, int y, int x, int b)
{
	int i;
	int pas;
	int	cmp;

	i = 0;
	cmp = grid->grid[y][x]->z - grid->grid[y + b][x + !b]->z;
	pas = ft_distance(grid->grid[y + b][x + !b], grid->grid[y][x]) / RES;
	while ((x + i / pas) < (x + RES))
	{
		if (!(cmp))
			ft_pix_put(grid, grid->grid[y][x], i / pas, b ? i : 0);
		else
			ft_pix_put(grid, grid->grid[y][x], i / pas, cmp > 0 ? i : -i);
		i++;
	}
}

int			ft_draw_lines(t_grid *grid)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			if (x + 1 < grid->size_x)
				ft_draw_lines_sub(grid, y, x, 0);
			if (y + 1 < grid->size_y)
				ft_draw_lines_sub(grid, y, x, 1);
			x++;
		}
		y++;
	}
	return (1);
}

int			ft_draw(char *file)
{
	t_grid	*grid;

	if ((grid = (ft_read(file))) == NULL)
		return (0);
	ft_draw_lines(grid);
	mlx_loop(grid->mlx);
	return (1);
}
