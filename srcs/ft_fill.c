/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 18:50:10 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/04 15:54:02 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_dist(t_point *a, t_point *b, t_point *c, t_point *d)
{
	int		maxy;

	maxy = 0;
	if ((a->z == b->z || (c->z == b->z && a->z > c->z)) && c->z == d->z)
		maxy = d->y - a->y;
	else if ((a->z == d->z || b->z == d->z) && b->z == c->z && a->z < b->z)
		maxy = a->y - b->y;
	else if ((a->z == b->z && a->z == d->z && a->z > c->z) || (a->z == c->z
	&& ((a->z == b->z && a->z > d->z) || (a->z == d->z && b->z > a->z))))
		maxy = d->y - b->y;
	else if (a->z == b->z && a->z == d->z && a->z != c->z)
		maxy = a->y - c->y;
	return (maxy);
}

int		ft_get_swit(t_point *a, t_point *b, t_point *c, t_point *d)
{
	int		swit;

	swit = 0;
	if ((a->z == b->z && c->z == d->z && a->z >= b->z) ||
	(a->z == b->z && a->z == d->z && a->z > c->z))
		swit = 1;
	else if (a->z == d->z && b->z == c->z && a->z < b->z)
		swit = 2;
	else if (a->z == d->z && a->z == b->z && a->z < c->z)
		swit = 3;
	else if (a->z == b->z && b->z == c->z && d->z < a->z)
		swit = 4;
	else if (b->z == c->z && b->z == d->z && a->z < c->z)
		swit = 5;
	else if (a->z == c->z && a->z == d->z && b->z > a->z)
		swit = 6;
	else if (b->z == c->z && b->z == d->z && a->z > c->z)
		swit = 7;
	return (swit);
}

int		ft_get_coef(t_point *a, t_point *b, t_point *c, t_point *d)
{
	int		pas;

	pas = 1;
	if (a->z == b->z && ((a->z == c->z && a->z > d->z) || c->z == d->z))
		pas = ft_distance(a, d);
	else if ((a->z == b->z || b->z == c->z) && b->z == d->z && a->z != c->z)
		pas = ft_distance(a, c);
	else if (a->z == d->z && a->z < b->z)
		pas = ft_distance(a, b);
	return (pas);
}

void	ft_put_cond(t_fdf *fdf, t_fill t, t_point *a)
{
	if (t.swit == 1)
		ft_pix_put(fdf, a, t.i + t.j / (t.coef / RES), t.j);
	if (t.swit == 2)
		ft_pix_put(fdf, a, t.i - t.j / (t.coef / RES), t.j + t.i);
	if (t.swit == 2 && t.dist % RES == 0)
		ft_pix_put(fdf, a, t.i - t.j / (t.coef / RES), t.j + t.i + 1);
	if (t.swit == 3 && t.i > t.j / (t.coef / RES))
		ft_pix_put(fdf, a, t.i + t.j / (t.coef / RES), t.i - t.j);
	if (t.swit == 3 && t.i > t.j / (t.coef / RES) && t.dist % RES == 0)
		ft_pix_put(fdf, a, t.i + t.j / (t.coef / RES), t.i - t.j + 1);
	if (t.swit == 4 && t.i > (t.j / (t.coef / RES)))
		ft_pix_put(fdf, a, t.i, t.j);
	if (t.swit == 5 && t.i < (t.j / (t.coef / RES)) && t.dist % RES == 0)
		ft_pix_put(fdf, a, t.i + t.j / (t.coef / RES), t.i - t.j + 1);
	if (t.swit == 5 && t.i < (t.j / (t.coef / RES)))
		ft_pix_put(fdf, a, t.i + t.j / (t.coef / RES), t.i - t.j);
	if (t.swit == 6 && t.i + (t.j / (t.coef / RES)) < RES)
		ft_pix_put(fdf, a, t.i + (t.j / (t.coef / RES)), t.i - t.j);
	if (t.swit == 6 && t.i + (t.j / (t.coef / RES)) < RES && t.dist % RES == 0)
		ft_pix_put(fdf, a, t.i + (t.j / (t.coef / RES)), t.i - t.j + 1);
	if (t.swit == 7 && t.i < (t.j / (t.coef / RES)))
		ft_pix_put(fdf, a, t.i + t.j / (t.coef / RES), t.j);
}
