/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/15 16:46:38 by fmadura          ###   ########.fr       */
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

static void ft_draw_line_int(t_grid *grid, t_point *p1, t_point *p2, int dir, int xmod, int ymod)
{
	int i;
	int pas;
	int cmp;

	i = 0;
	cmp = p1->z - p2->z;
	pas = ft_distance(p1, p2) / RES;
	while ((p1->x + i / pas) < (p1->x + RES))
	{
		if (p1->y + (cmp > 0 ? i : -i) - ymod < p1->y - ymod)
		{
			if (!(cmp))
				ft_pix_put(grid, p1, i / pas + xmod, (dir ? i : 0) - ymod);
			else
				ft_pix_put(grid, p1, i / pas + xmod, (cmp > 0 ? i : -i) - ymod);
		}
		i++;
	}
}


static void ft_draw_line_one(t_grid *grid, t_point *p1, t_point *p2, int dir)
{
	int i;
	int pas;
	int cmp;

	i = 0;
	cmp = p1->z - p2->z;
	pas = ft_distance(p1, p2) / RES;
	while ((p1->x + i / pas) < (p1->x + RES))
	{
		if (!(cmp))
			ft_pix_put(grid, p1, i / pas, dir ? i : 0);
		else
			ft_pix_put(grid, p1, i / pas, cmp > 0 ? i : -i);
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
				ft_draw_line_one(grid, grid->grid[y][x], grid->grid[y][x + 1], 0);
			if (y + 1 < grid->size_y)
				ft_draw_line_one(grid, grid->grid[y][x], grid->grid[y + 1][x], 1);
			if (y + 1 < grid->size_y && x + 1 < grid->size_x)
			{
				int xi = 0;
				int yi;
				while (xi < RES)
				{
					yi = 0;
					while (yi < RES)
					{
						ft_draw_line_int(grid, grid->grid[y][x], grid->grid[y + 1][x], 1, xi, yi);	
						yi++;
					}
					xi++;
				}
			}
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
