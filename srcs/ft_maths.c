/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:40:52 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 17:57:01 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_distance(t_point *p1, t_point *p2)
{
	return (ft_pythagore(p1->y - p2->y, p1->x - p2->x));
}

int		ft_pythagore(int a, int b)
{
	return ((int)sqrt(pow(a, 2) + pow(b, 2)));
}
