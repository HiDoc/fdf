/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:39:48 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 17:58:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_draw_line_temp(t_fdf *fdf, t_point *p1, t_point *p2, int dir)
{
	int		i;
	int		coef;
	int		cmp;
	int		color;
	float	percent;

	i = 0;
	cmp = p1->z - p2->z;
	coef = fdf_coef(fdf, p1, p2);
	while (i < fdf->res * coef)
	{
		percent = ((float)i / (float)coef) / (float)fdf->res;
		color = fdf_color_mixer(p1->color, p2->color, percent);
		if (!(cmp))
			fdf_pix_put_color(fdf,
			p1->x + i, p1->y + (!dir ? i : -i), color);
		else if (cmp > 0)
			fdf_pix_put_color(fdf, p1->x + i / coef, p1->y + i, color);
		else
			fdf_pix_put_color(fdf,
			p1->x + i / coef, p1->y - (p1->y == p2->y ? -i : i), color);
		i++;
	}
}

int			fdf_draw_lines_temp(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point *a;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			a = fdf->grid[y][x];
			if (x + 1 < fdf->size_x[y])
				fdf_draw_line_temp(fdf, a, fdf->grid[y][x + 1], 1);
			if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				fdf_draw_line_temp(fdf, a, fdf->grid[y + 1][x], 0);
			x++;
			mlx_do_sync(fdf->mlx);
		}
		y++;
	}
	return (1);
}

static void	fdf_draw_line(t_fdf *fdf, t_point *p1, t_point *p2, int dir)
{
	int		i;
	int		coef;
	int		cmp;
	int		color;
	float	percent;

	i = 0;
	cmp = p1->z - p2->z;
	coef = fdf_coef(fdf, p1, p2);
	while (i < fdf->res * coef)
	{
		percent = ((float)i / (float)coef) / (float)fdf->res;
		color = fdf_color_mixer(p1->color, p2->color, percent);
		if (!(cmp))
			fdf_pix_put_color(fdf,
			p1->x + i, p1->y + (!dir ? i : -i), color);
		else if (cmp > 0)
			fdf_pix_put_color(fdf, p1->x + i / coef, p1->y + 
			(coef == 1 && cmp == 1 ? 0 : i), color);
		else
			fdf_pix_put_color(fdf,
			p1->x + i / coef, p1->y - (p1->y == p2->y ? 0 : i), color);
		i++;
	}
}

int			fdf_draw_lines(t_fdf *fdf)
{
	int		y;
	int		x;
	t_point *a;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			a = fdf->grid[y][x];
			if (x + 1 < fdf->size_x[y])
				fdf_draw_line(fdf, a, fdf->grid[y][x + 1], 1);
			if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				fdf_draw_line(fdf, a, fdf->grid[y + 1][x], 0);
			x++;
		}
		y++;
	}
	return (1);
}

int			fdf_draw(char *file)
{
	t_fdf	*fdf;

	if ((fdf = (fdf_read(file))) == NULL)
		return (0);
	fdf_add_mlx(fdf);
	fdf_draw_lines(fdf);
	mlx_do_sync(fdf->mlx);
	fdf->rand = fdf_random((int)&fdf->rand);
	mlx_key_hook(fdf->win, &key_hook, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
