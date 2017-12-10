/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:29:19 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/08 16:36:33 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point			*ft_new_point(int z)
{
	t_point	*point;

	if ((point = (t_point *)malloc(sizeof(t_point))) == NULL)
		return (NULL);
	point->z = z;
	point->color = "0x00FFFFFF";
	return (point);
}
