/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 19:01:30 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/03 19:01:33 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_fill_sub(t_grid *grid, t_trngl t, t_point *a, int dist)
{
	int i;
	int j;

	i = 0;
	while (i < RES)
	{
		j = 0;
		while (j < t.dist)
		{
			t.i = i;
			t.j = j;
			if (!dist)
				ft_put_cond(grid, t, a);
			else
			{
				if (t.swit == 4 && i + j / (t.coef / RES) < RES)
					ft_pix_put(grid, a, i, j + i);
				if (t.swit == 6 && i < j / (t.coef / RES))
					ft_pix_put(grid, a, i, j);
			}
			j++;
		}
		i++;
	}
}

static void	ft_fill(t_grid *grid, int x, int y)
{
	t_point *a;
	t_point *b;
	t_point *c;
	t_point *d;
	t_trngl t;

	a = grid->grid[y][x];
	b = grid->grid[y][x + 1];
	c = grid->grid[y + 1][x + 1];
	d = grid->grid[y + 1][x];
	t.coef = ft_get_coef(a, b, c, d);
	t.dist = ft_get_dist(a, b, c, d);
	t.swit = ft_get_swit(a, b, c, d);
	if (t.swit > 0)
		ft_fill_sub(grid, t, (t.swit == 2 ? b : a), 0);
	if (t.swit == 4 || t.swit == 6)
		ft_fill_sub(grid, t, b, t.swit == 4 ? t.dist : ft_distance(b, c));
}

static void	ft_draw_line_one(t_grid *grid, t_point *p1, t_point *p2, int dir)
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
			ft_pix_put_l(grid, p1, i / pas, dir ? i : 0);
		else
		{
			if (cmp > 0)
				ft_pix_put_l(grid, p1, i / pas, i);
			else
				ft_pix_put_l(grid, p1, i / pas, dir ? 0 : -i);
		}
		i++;
	}
}

int			ft_draw_lines(t_grid *grid)
{
	int		y;
	int		x;
	t_point *a;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			a = grid->grid[y][x];
			if (y + 1 < grid->size_y && x + 1 < grid->size_x)
				ft_fill(grid, x, y);
			if (x + 1 < grid->size_x)
				ft_draw_line_one(grid, a, grid->grid[y][x + 1], 0);
			if (y + 1 < grid->size_y)
				ft_draw_line_one(grid, a, grid->grid[y + 1][x], 1);
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
