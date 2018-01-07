/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:40:52 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/07 14:33:09 by fmadura          ###   ########.fr       */
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
