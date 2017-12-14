/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/14 10:24:14 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_pixel_put(t_grid *grid, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(grid->mlx,
			grid->win,
			point->x + xmod,
			point->y + ymod,
			0x00BB0000);
}

static int	ft_draw_lines_sub(t_grid *grid, int y, int m1, int m2)
{
	int tmp;
	int	x;
	int pas;
	int distance;

	x = 0;
	while ((m2 ? x + 1 : x) < grid->size_x && (m1 ? y + 1 : y < grid->size_y))
	{
		tmp = 0;
		distance = ft_distance(grid->grid[y + m1][x + m2], grid->grid[y][x]);
		pas = distance / RES;
		while (tmp < distance && x + tmp/pas < x + RES)
		{
			if ((grid->grid[y][x])->z == (grid->grid[y + m1][x + m2])->z)
				ft_pixel_put(grid, grid->grid[y][x], tmp / pas, m1 ? tmp : 0);
			else
				ft_pixel_put(grid, grid->grid[y][x], tmp / pas, 
				(grid->grid[y][x])->z > (grid->grid[y + m1][x + m2])->z ? tmp : -tmp);
			tmp++;
		}
		x++;
	}
	return (1);
}
static int	ft_draw_lines_sub2(t_grid *grid, int y, int m1, int m2)
{
	int tmp;
	int x;
	int pas;
	int distance;

	x = 0;
	while (x < grid->size_x)
	{
		tmp = 0;
		if (y + 1 < grid->size_y)
		{
			distance = ft_distance(grid->grid[y + m1][x + m2], grid->grid[y][x]);
			pas = distance / RES;
			while (tmp < distance && x + tmp / pas < x + RES)
			{
				if ((grid->grid[y][x])->z == (grid->grid[y + m1][x + m2])->z)	
					mlx_pixel_put(grid->mlx, grid->win,
							grid->grid[y][x]->x + tmp / pas,
							grid->grid[y][x]->y + tmp, 0x000000BB);
				else
					mlx_pixel_put(grid->mlx, grid->win, 
							grid->grid[y][x]->x + tmp / pas,
							grid->grid[y][x]->y + (grid->grid[y][x]->z >
							grid->grid[y + m1][x + m2]->z ? tmp : -tmp), 0x00BB0000);
				tmp++;
			}
		}
		mlx_pixel_put(grid->mlx, grid->win, grid->grid[y][x]->x, grid->grid[y][x]->y, 0x00FFFFFF);
		x++;
	}
	return (1);
}
int			ft_draw_lines(t_grid *grid)
{
	int		y;

	y = 0;
	while (y < grid->size_y)
	{
		ft_draw_lines_sub(grid, y, 0, 1);
		ft_draw_lines_sub2(grid, y, 1, 0);
		y++;
	}
	return (1);
}

int		ft_draw(char *file)
{
	t_grid	*grid;
	if ((grid = (ft_read(file))) == NULL)
		return (0);
	ft_draw_lines(grid);
	mlx_loop(grid->mlx);
	return (1);
}
