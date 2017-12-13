/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 18:45:23 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_draw_lines_sub(t_grid *grid, int y)
{
	int tmp;
	int	x;
	int pas;
	int distance;

	x = 0;
	while (x + 1 < grid->size_x)
	{
		tmp = 0;
		distance = ft_distance(grid->grid[y][x + 1], grid->grid[y][x]);
		pas = distance / RES;
		while (tmp < distance && grid->grid[y][x]->x + tmp/pas < grid->grid[y][x + 1]->x)
		{
			if ((grid->grid[y][x])->z == (grid->grid[y][x + 1])->z)
				mlx_pixel_put(grid->mlx, grid->win,
				grid->grid[y][x]->x + tmp / pas, grid->grid[y][x]->y, 0x00BB0000);
			else
				mlx_pixel_put(grid->mlx, grid->win, grid->grid[y][x]->x + tmp/pas, 
				grid->grid[y][x]->y + ((grid->grid[y][x])->z > 
				(grid->grid[y][x + 1])->z ? tmp : -tmp), 0x00AA22AA);
			tmp++;
		}
		x++;
	}
	return (1);
}

int		ft_draw_lines(t_grid *grid)
{
	int		y;

	y = 0;
	while (y < grid->size_y)
	{
		ft_draw_lines_sub(grid, y);
		y++;
	}
	return (1);
}

int		ft_draw_lines2(t_grid *grid)
{
	int		x;
	int		y;
	int		tmp;
	int		tmp2;
	int		distance;
	int		pas;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			tmp = 0;
			tmp2 = 0;
			pas = 0;	
			if (y + 1 < grid->size_y)
			{
				distance = ft_distance(grid->grid[y + 1][x], grid->grid[y][x]);
				while (tmp < distance && grid->grid[y][x]->x + tmp2 < grid->grid[y + 1][x]->x)
				{
					pas = distance / RES;
					if ((grid->grid[y][x])->z == (grid->grid[y + 1][x])->z)	
						mlx_pixel_put(grid->mlx, grid->win, grid->grid[y][x]->x + tmp2, grid->grid[y][x]->y + tmp, 0x000000BB);
					else
						mlx_pixel_put(grid->mlx, grid->win, grid->grid[y][x]->x + tmp2, grid->grid[y][x]->y -
								(grid->grid[y][x]->z > grid->grid[y + 1][x]->z ? -tmp : tmp),
								0x00BB0000);
					tmp++;
					tmp2 += tmp % pas == 0; 
				}
			}
			mlx_pixel_put(grid->mlx, grid->win, grid->grid[y][x]->x, grid->grid[y][x]->y, 0x00FFFFFF);
			x++;
		}
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
	ft_draw_lines2(grid);
	mlx_loop(grid->mlx);
	return (1);
}
