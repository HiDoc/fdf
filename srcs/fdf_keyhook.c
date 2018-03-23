/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:39:48 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/23 09:10:49 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_reset(int keycode, t_fdf *fdf)
{
	if (keycode == 15)
	{
		fdf_res_grid(fdf);
		return (1);
	}
	return (0);
}

static int	key_move(int keycode, t_fdf *fdf)
{
	if (keycode == 123 || keycode == 124)
		fdf->x_center_mod += (fdf->res * (keycode == 123 ? 1 : -1));
	else if (keycode == 125 || keycode == 126)
		fdf->y_center_mod -= (fdf->res * (keycode == 125 ? 1 : -1));
	else
		return (0);
	return (1);
}

int			key_zoom(int keycode, t_fdf *fdf)
{
	if (keycode == 69 || keycode == 78)
	{
		if (fdf->res > 19)
			fdf->res = (int)fdf->res + ((int)fdf->res / 20) *
				(keycode == 78 ? -1 : 1);
		else if (fdf->res > 1)
			fdf->res = (int)fdf->res + (keycode == 78 ? -1 : 1);
		else
			fdf->res = fdf->res + ((fdf->res * 0.1) * (keycode == 78 ? -1 : 1));
		fdf_map_point(&fdf_posx, fdf, 'x');
		fdf_map_point(&fdf_posy, fdf, 'y');
		fdf_max_y(fdf);
		fdf_max_x(fdf);
		fdf->x_center = fdf->x_win / 2 - fdf->x_end / 2;
		fdf->y_center = fdf_labs(fdf->y_start) + fdf->y_win / 2
			- (fdf->y_end - fdf->y_start) / 2;
		return (1);
	}
	return (0);
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
	return (0);
}

int			key_hook(int keycode, void *param)
{
	t_fdf	*fdf;
	int		hooked;

	fdf = param;
	hooked = 0;
	if (keycode == 8 && fdf->size_y < 25)
	{
		fdf->rand = fdf_random(fdf->rand);
		fdf_map_point(&fdf_rncg, fdf, 'c');
		fdf_draw_lines_temp(fdf);
	}
	else
	{
		hooked += key_move(keycode, fdf);
		hooked += key_reset(keycode, fdf);
		hooked += key_zoom(keycode, fdf);
		hooked += key_exit(keycode, fdf);
		hooked += key_color(keycode, fdf);
		if (hooked)
		{
			mlx_clear_window(fdf->mlx, fdf->win);
			fdf_draw_lines(fdf);
		}
	}
	return (1);
}
