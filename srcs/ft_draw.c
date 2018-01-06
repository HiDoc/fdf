/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 19:01:30 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/06 18:20:48 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_quad(t_fdf *fdf, int x, int y, t_point *a)
{
	int i = 0;
	int j = 0;
	t_point *b = fdf->grid[y][x + 1];
	t_point *c = fdf->grid[y + 1][x];
	int hauteur;

   	hauteur = a->z == b->z ? fdf->grid[y + 1][x + 1]->y - a->y : a->y - b->y;
	while (i < fdf->res)
	{
		j = 0;
		while (j < hauteur)
		{
			if (a->z == b->z)
			{
				if (a->z == b->z && a->z == c->z)
					ft_pix_put_flat(fdf, a, i + j / ft_coef(fdf, a, c), j);
				else
					ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, c), j);
			}
			else if (a->z != b->z)
			{	
				ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, b), -j + i);
				ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, b), -j + i + 1);
			}
			j++;
		}
		i++;
	}
}

static void	ft_trg(t_fdf *fdf, t_point *a, t_point *b, t_point *c)
{
	int i = 0;
	int j = 0;
	int hauteur;

	hauteur = fmax(fmax(a->z, b->z), fmax(c->z, 1)) - fmin(fmin(a->z, b->z),c->z);
	if ((c->y > b->y && c->y <= a->y && c->z == a->z && a->z < b->z))
		hauteur++;
	if (a->y > b->y && a->y < c->y && a->z >= c->z&&b->x == c->x && c->z < b->z && i >= j / ft_coef(fdf, a, b))
		hauteur++;
	else if (a->y == b->y && a->y < c->y)
		hauteur++;
	else if (b->z == c->z && a->z > c->z)	
		hauteur++;
	while (i < fdf->res)
	{
		j = 0;
		while (j < fdf->res * hauteur)
		{
			if (a->y > b->y && a->y < c->y  &&  a->z >= c->z && c->z <= b->z)
			{
				if (b->x != c->x && i < j /ft_coef(fdf, b, c))
				{
					ft_pix_put(fdf, b, -i - j / ft_coef(fdf, b,c),j -i );
					ft_pix_put(fdf, b, -i - j / ft_coef(fdf, b,c),j -i +1 );
				}
				else if (b->x == c->x && i > j / ft_coef(fdf, a, b))
				{
					ft_pix_put(fdf, c, -i + j / ft_coef(fdf, a, b), -j -i);
					ft_pix_put(fdf, c, -i + j / ft_coef(fdf, a, b), -j -i + 1);
				}
			}
		else if ((c->y > b->y && c->y <= a->y && c->z == a->z && a->z < b->z) && i < j / ft_coef(fdf, b, c))
				ft_pix_put(fdf, b, i, j);
			else 	if (a->y == b->y && a->y < c->y && a->z != c->z&& i + j / ft_coef(fdf, a,c) <= fdf->res)
				ft_pix_put(fdf, a, i + j / ft_coef(fdf, a,c), j);
			else if (a->y > b->y && a->y > c->y && b->z == c->z && i - j / ft_coef(fdf, a,c) >= 0)
			{
				ft_pix_put(fdf, b, i - j / ft_coef(fdf, a,c), j + i);
				ft_pix_put(fdf, b, i - j / ft_coef(fdf, a,c), j + i + 1);
			}
			else if (b->z == c->z && a->y < c->y && i - j / ft_coef(fdf, a,b) < 0 && ft_distance(a,b) > fdf->res
					&& ft_distance(b,c) == fdf->res)	
				ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, b), j);
			else if (a->z > b->y && a->y > c->y && b->z == c->z && i - j / ft_coef(fdf, a,c) >= 0)
				ft_pix_put(fdf, a, i, j);
			j++;
		}
		i++;
	}
}

static void	ft_fill(t_fdf *fdf, int x, int y)
{
	t_point *a;
	t_point *b;
	t_point *c;
	t_point *d;

	a = fdf->grid[y][x];
	b = fdf->grid[y][x + 1];
	c = fdf->grid[y + 1][x + 1];
	d = fdf->grid[y + 1][x];
	(void)ft_quad;
	if ((a->z == b->z && c->z == d->z && a->z >= c->z) || (a->z == d->z && b->z == c->z && a->z < b->z))
		ft_quad(fdf, x, y, a);
	else	
	{
		ft_trg(fdf, a, b, d);	
		ft_trg(fdf, d, b, c);	
		if ((b->z == c->z && b->z == d->z && a->z > b->z) || (a->z == d->z && a->z == b->z && a->z < c->z))
		{
			ft_trg(fdf, a, c, d);
		}
	}
}

static void	ft_draw_line_one(t_fdf *fdf, t_point *p1, t_point *p2, int dir)
{
	int		i;
	int		coef;
	int		cmp;

	i = 0;
	cmp = p1->z - p2->z;
	coef = ft_distance(p1, p2) / fdf->res;
	while (i / coef < fdf->res)
	{
		if (!(cmp))
			ft_pix_put_l(fdf, p1, i / coef, dir ? i : 0);
		else
		{
			if (cmp > 0)
				ft_pix_put_l(fdf, p1, i / coef, i);
			else
				ft_pix_put_l(fdf, p1, i / coef, dir ? 0 : -i);
		}
		i++;
	}
}

int			ft_draw_lines(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point *a;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			a = fdf->grid[y][x];
			if (y + 1 < fdf->size_y && x + 1 < fdf->size_x[y] && x + 1 < fdf->size_x[y + 1])
				ft_fill(fdf, x, y);
			if (x + 1 < fdf->size_x[y])
				ft_draw_line_one(fdf, a, fdf->grid[y][x + 1], 0);
			if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				ft_draw_line_one(fdf, a, fdf->grid[y + 1][x], 1);
			x++;
		}
		y++;
	}
	return (1);
}

int			ft_draw(char *file)
{
	t_fdf	*fdf;

	if ((fdf = (ft_read(file))) == NULL)
		return (0);
	ft_draw_lines(fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
