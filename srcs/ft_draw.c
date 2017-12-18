/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/18 11:58:42 by fmadura          ###   ########.fr       */
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

/*static void ft_draw_line_int(t_grid *grid, t_point *p1, t_point *p2, t_point *p3, int dir, int xmod, int ymod)
{
	int i;
	int pas;
	int pas2;

	i = 0;
	(void)xmod;
	(void)ymod;
	(void)dir;
	(void)grid;
	pas = ft_distance(p1, p2) / RES;
	pas2 = ft_distance(p2, p3) / RES;
	while (i / pas < RES)
	{
		//if (i <= ymod  && i / pas + xmod >= RES)
		//	ft_pix_put(grid, p1, i / pas + xmod, (dir ? i : 0) - ymod);
		//if (i <= ymod && i / pas + xmod < RES)
		//	ft_pix_put(grid, p1, i / pas + xmod, (dir ? i : 0) - ymod);
		//if (i >= ymod && i / pas + xmod > RES)
		//	ft_pix_put(grid, p1, i / pas + xmod, (dir ? i : 0) - ymod);
		//if (i >= ymod && i / pas + xmod < RES)
		//	ft_pix_put(grid, p1, i / pas + xmod, (dir ? i : 0) - ymod);
		i++;
	}
}*/

static void ft_draw_notflat(t_grid *grid, int x, int y)
{
	int pasx;
	int pasy;
	int i;
	int j;
	int cmp;

	j = 2;
	pasx = ft_distance(grid->grid[y][x], grid->grid[y][x + 1]) / RES;
	cmp = grid->grid[y][x]->z - grid->grid[y][x + 1]->z;
	pasy = ft_distance(grid->grid[y][x], grid->grid[y + 1][x]) / RES;
	while (j + 1 < RES && j < grid->grid[y][x]->x)
	{
		i = 2;
		while (i / pasx + 1 < RES)
		{
			ft_pix_put(grid, grid->grid[y][x], i / pasx + j, (cmp > 0 ? j : -j));
			i++;
		}
		j++;
	}
}


static void ft_draw_flat(t_grid *grid, int x, int y)
{
	int pas;
	int i;
	int j;

	j = 2;
	pas = ft_distance(grid->grid[y][x], grid->grid[y][x + 1]) / RES;
	while (j + 1 < RES)
	{
		i = 2;
		while (i / pas + 1 < RES)
		{
			ft_pix_put(grid, grid->grid[y][x], i / pas + j, j);
			i++;
		}
		j++;
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
	while (i / pas < RES)
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
				if (grid->grid[y][x]->z == grid->grid[y][x + 1]->z
					&& grid->grid[y + 1][x]->z == grid->grid[y][x]->z
					&& grid->grid[y][x]->z == grid->grid[y + 1][x + 1]->z)
					ft_draw_flat(grid, x, y);
				else
					ft_draw_notflat(grid, x, y);
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
