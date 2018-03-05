/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_maths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:40:15 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 17:34:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_distance(t_point *p1, t_point *p2)
{
	return (fdf_pythagore(p1->y - p2->y, p1->x - p2->x));
}

int		fdf_coef(t_fdf *fdf, t_point *p1, t_point *p2)
{
	int coef;

	coef = (fdf_distance(p1, p2) / fdf->res);
	return (!coef ? 1 : coef);
}

int		fdf_pythagore(int a, int b)
{
	return ((int)sqrt(pow(a, 2) + pow(b, 2)));
}

int		fdf_rand(int seed, int increment, int modulus, int multiplier)
{
	return ((multiplier * seed + increment) % modulus);
}

int		fdf_random(int seed)
{
	return (fdf_rand(seed, 1013904223, INT_MAX, 1664525));
}
