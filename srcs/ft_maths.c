/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:40:52 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/04 12:53:08 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_distance(t_point *p1, t_point *p2)
{
	return (ft_pythagore(p1->y - p2->y, p1->x - p2->x));
}

int		ft_coef(t_fdf *fdf, t_point *p1, t_point *p2)
{
	int coef;

	coef = (ft_distance(p1, p2) / fdf->res);
	return (!coef ? 1 : coef);
}

int		ft_pythagore(int a, int b)
{
	return ((int)sqrt(pow(a, 2) + pow(b, 2)));
}

int		ft_rand(int seed, int increment, int modulus, int multiplier)
{
	return ((multiplier * seed + increment) % modulus);
}

int		ft_random(int seed)
{
	return (ft_rand(seed, 1013904223, INT_MAX, 1664525));
}
