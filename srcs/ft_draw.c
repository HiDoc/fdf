/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 19:01:30 by fmadura           #+#    #+#             */
/*   Updated: 2018/02/19 16:15:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_quad(t_fdf *fdf, int x, int y, t_point *a)
{
	int		i;
	int		j;
	t_point	*b;
	t_point	*c;
	int		hauteur;

	b = fdf->grid[y][x + 1];
	c = fdf->grid[y + 1][x];
	hauteur = (a->z == b->z ? fdf->grid[y + 1][x + 1]->y - a->y : a->y - b->y);
	i = 0;
	while (i <= fdf->res)
	{
		j = 0;
		while (j <= hauteur)
		{
			if (a->z == b->z)
			{
				if (a->z == b->z && a->z == c->z)
					ft_pix_put_flat(fdf, a, i + j / ft_coef(fdf, a, c), j);
				else
					ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, c), j);
			}
			else
			{
				ft_pix_put_top(fdf, a, i + j / ft_coef(fdf, a, b), -j + i);
				ft_pix_put_top(fdf, a, i + j / ft_coef(fdf, a, b), -j + i + 1);
			}
			j++;
		}
		i++;
	}
}

static void trg_left(t_fdf *fdf, t_point *a, t_point *b, t_point *c)
{
	int		i;
	int		j;
	int		hauteur;

	i = 0;
	hauteur = fmax(fmax(a->z, b->z), fmax(c->z, 1)) -
		fmin(fmin(a->z, b->z), c->z);
	if (a->y > b->y && a->y < c->y && a->z >= c->z && b->x == c->x && c->z < b->z)
		hauteur++;
	while (i <= fdf->res)
	{
			j = 0;
		while (j < fdf->res * hauteur)
		{
			if (b->x != c->x && i < j / ft_coef(fdf, b, c))
			{
				ft_pix_put(fdf, b, -i - j / ft_coef(fdf, b, c), j - i);
				ft_pix_put(fdf, b, -i - j / ft_coef(fdf, b, c), j - i + 1);
			}
			else if (b->x == c->x && i > j / ft_coef(fdf, a, b))
			{
				ft_pix_put(fdf, c, -i + j / ft_coef(fdf, a, b), -j - i);
				ft_pix_put(fdf, c, -i + j / ft_coef(fdf, a, b), -j - i + 1);
			}
			j++;
		}
		i++;
	}

}

static void	ft_trg(t_fdf *fdf, t_point *a, t_point *b, t_point *c)
{
	int		i;
	int		j;
	int		hauteur;

	i = 0;
	hauteur = fmax(fmax(a->z, b->z), fmax(c->z, 1)) -
		fmin(fmin(a->z, b->z), c->z);
	if ((c->y > b->y && c->y <= a->y && c->z == a->z && a->z < b->z))
		hauteur++;
	if (a->y > b->y && a->y < c->y && a->z >= c->z && b->x == c->x &&
			c->z < b->z)
		hauteur++;
	else if (a->y == b->y && a->y < c->y)
		hauteur++;
	else if (b->z == c->z && a->z > c->z)
		hauteur++;
	while (i <= fdf->res)
	{
		j = 0;
		while (j <= fdf->res * hauteur)
		{
			if (a->y > b->y && a->y < c->y && a->z >= c->z && c->z <= b->z)
			{
				if (b->x != c->x && i < j / ft_coef(fdf, b, c))
				{
					ft_pix_put(fdf, b, -i - j / ft_coef(fdf, b, c), j - i);
					ft_pix_put(fdf, b, -i - j / ft_coef(fdf, b, c), j - i + 1);
				}
				else if (b->x == c->x && i > j / ft_coef(fdf, a, b))
				{
					ft_pix_put(fdf, c, -i + j / ft_coef(fdf, a, b), -j - i);
					ft_pix_put(fdf, c, -i + j / ft_coef(fdf, a, b), -j - i + 1);
				}
			}
			else if ((c->y > b->y && c->y <= a->y && c->z == a->z &&
						a->z < b->z) && i < j / ft_coef(fdf, b, c))
				ft_pix_put(fdf, b, i, j);
			else if (a->y == b->y && a->y < c->y && a->z != c->z &&
					i + j / ft_coef(fdf, a, c) <= fdf->res)
				ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, c), j);
			else if (a->y > b->y && a->y > c->y && b->z == c->z &&
					i - j / ft_coef(fdf, a, c) >= 0)
			{
				ft_pix_put(fdf, b, i - j / ft_coef(fdf, a, c), j + i);
				ft_pix_put(fdf, b, i - j / ft_coef(fdf, a, c), j + i + 1);
			}
			else if (b->z == c->z && a->y < c->y && i - j / ft_coef(fdf, a, b) <
					0 && ft_distance(a, b) > fdf->res && ft_distance(b, c) == fdf->res)
				ft_pix_put(fdf, a, i + j / ft_coef(fdf, a, b), j);
			else if (a->z > b->y && a->y > c->y && b->z == c->z &&
					i - j / ft_coef(fdf, a, c) >= 0)
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
	(void)ft_trg;
	if ((a->z == b->z && c->z == d->z && a->z >= c->z) ||
			(a->z == d->z && b->z == c->z && a->z < b->z))
			;//ft_quad(fdf, x, y, a);
	else
	{
		if (a->y > b->y && a->y < d->y && a->z >= d->z && d->z <= b->z)
			trg_left(fdf, a,b, d);
		//ft_trg(fdf, a, b, d);
		//ft_trg(fdf, d, b, c);
		//if ((b->z == c->z && b->z == d->z && a->z > b->z) ||
		//		(a->z == d->z && a->z == b->z && a->z < c->z))
		//	ft_trg(fdf, a, c, d);
	}
}

static void	ft_draw_line_one(t_fdf *fdf, t_point *p1, t_point *p2, int dir)
{
	int		i;
	int		coef;
	int		cmp;

	i = 0;
	cmp = p1->z - p2->z;
	coef = ft_coef(fdf, p1, p2);
	while (i / coef < fdf->res)
	{
		if (!(cmp))
			ft_pix_put_flat(fdf, p1, i / coef, dir ? i : 0);
		else if (cmp > 0)
			ft_pix_put_flat(fdf, p1, i / coef, i);
		else
			ft_pix_put_flat(fdf, p1, i / coef, dir ? 0 : -i);
		i++;
	}
}

int			ft_draw_lines(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point *a;

	(void)ft_draw_line_one;
	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			a = fdf->grid[y][x];
			if (y + 1 < fdf->size_y && x + 1 < fdf->size_x[y] &&
					x + 1 < fdf->size_x[y + 1])
				ft_fill(fdf, x, y);
			else if (x + 1 < fdf->size_x[y])
				ft_draw_line_one(fdf, a, fdf->grid[y][x + 1], 0);
			else if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				ft_draw_line_one(fdf, a, fdf->grid[y + 1][x], 1);
			x++;
		}
		y++;
	}
	return (1);
}

int			key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (fdf->img != NULL)
		mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image (fdf->mlx, 800, 800);

	if (keycode == 123)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 400, 400); 
	}
	if (keycode == 124)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 400, 400); 
	}
	if (keycode == 125)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0); 
	}
	if (keycode == 126)
	{
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 800, 800); 
	}
	return (1);
}

int			ft_draw(char *file)
{
	t_fdf	*fdf;

	if ((fdf = (ft_read(file))) == NULL)
		return (0);
	ft_draw_lines(fdf);
	fdf->img = NULL;
	mlx_key_hook(fdf->win, &key_hook, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
