/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhook_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:19:15 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/23 09:03:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_color(int code, t_fdf *fdf)
{
	int i;

	i = 0;
	if (code == 17)
		fdf->color = fdf_random(fdf->rand);
	else if (code == 11)
		fdf->color2 = fdf_random(fdf->rand);
	else if (code == 13)
		while (i < 50)
		{
			mlx_clear_window(fdf->mlx, fdf->win);
			key_color(11, fdf);
			fdf_draw_lines(fdf);
			mlx_do_sync(fdf->mlx);
			mlx_clear_window(fdf->mlx, fdf->win);
			key_color(17, fdf);
			fdf_draw_lines(fdf);
			mlx_do_sync(fdf->mlx);
			i++;
		}
	else
		return (0);
	fdf->rand = fdf_random(fdf->rand);
	fdf_map_point(&fdf_colr, fdf, 'c');
	return (1);
}
