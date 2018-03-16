/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:39:48 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/16 11:42:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_reset(int keycode, t_fdf *fdf)
{
	if (keycode == 15)
		fdf_res_grid(fdf);
	return (1);
}

static int	key_move(int keycode, t_fdf *fdf)
{
	if (keycode == 123 || keycode == 124)
		fdf->x_center = fdf->x_center + fdf->res * (keycode == 123 ? 1 : -1);
	if (keycode == 125 || keycode == 126)
		fdf->y_center = fdf->y_center + fdf->res * (keycode == 126 ? 1 : -1);
	return (1);
}

static int	key_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == 69 || keycode == 78)
	{
		if (fdf->res > 19)
			fdf->res = fdf->res + (fdf->res / 20) * (keycode == 78 ? -1 : 1);
		else
			fdf->res = fdf->res + (keycode == 78 ? -1 : 1);
		if (fdf->res < 1)
			fdf->res = 1;
		fdf_map_point(&fdf_posx, fdf, 'x');
		fdf_map_point(&fdf_posy, fdf, 'y');
		fdf_max_y(fdf);
		fdf_max_x(fdf);
		fdf->x_center = fdf->x_win / 2 - fdf->x_end / 2;
		fdf->y_center = abs(fdf->y_start) + fdf->y_win / 2
			- (fdf->y_end - fdf->y_start) / 2;
	}
	return (1);
}

static int	key_exit(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		mlx_destroy_window(fdf->mlx, fdf->win);
		fdf_clear_fdf(fdf);
		exit(0);
	}
	return (1);
}

int			key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keycode == 8)
	{
		fdf->rand = fdf_random(fdf->rand);
		fdf_map_point(&fdf_rncg, fdf, 'c');
		fdf_draw_lines_temp(fdf);
	}
	else
	{
		key_move(keycode, fdf);
		key_reset(keycode, fdf);
		key_zoom(keycode, fdf);
		key_exit(keycode, fdf);
		mlx_clear_window(fdf->mlx, fdf->win);
		fdf_draw_lines(fdf);
	}
	return (1);
}
