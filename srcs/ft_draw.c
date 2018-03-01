/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 19:01:30 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/01 20:11:32 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_color_mixer(int c1, int c2, float mix)
{
	int		r;
	int		g;
	int		b;

	r = ((c1 & 0xFF0000) * (1 - mix) + (c2 & 0xFF0000) * (mix));
	g = ((c1 & 0x00FF00) * (1 - mix) + (c2 & 0x00FF00) * (mix));
	b = ((c1 & 0x0000FF) * (1 - mix) + (c2 & 0x0000FF) * (mix));
	return (r + g + b);
}

static void	ft_draw_line_one(t_fdf *fdf, t_point *p1, t_point *p2, int dir)
{
	int		i;
	int		coef;
	float	percent;
	int		cmp;
	int 	color;

	i = 0;
	cmp = p1->z - p2->z;
	coef = ft_coef(fdf, p1, p2);
	while (i / coef < fdf->res)
	{
		percent = ((float)i / (float)coef) / ABS(cmp);
		color = ft_color_mixer(p1->color, p2->color, percent);
		if (!(cmp))
			ft_pix_put_flat(fdf, p1, i / coef, dir ? i : 0);
		else if (cmp > 0)
		{
			ft_pix_put_color(fdf, p1->x + i / coef, p1->y + i, color);
		}
		else
			ft_pix_put_color(fdf, p1->x + i / coef, p1->y + (dir ? 0: -i), color);
		i++;
	}
}

int			ft_draw_lines(t_fdf *fdf)
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
				ft_draw_line_one(fdf, a, fdf->grid[y][x + 1], 0);
			if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				ft_draw_line_one(fdf, a, fdf->grid[y + 1][x], 1);
			x++;
		}
		y++;
	}
	return (1);
}

int			key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	printf("%d \n", keycode);
	if (keycode == 69 || keycode == 78)
	{
		fdf->res = fdf->res + (keycode == 78 ? -1 : 1);
		if (fdf->res < 1)
			fdf->res = 1;
		ft_ini_fdf(fdf, fdf->res);	
	}
	if (keycode == 15)
		ft_res_grid(fdf);
	if (keycode == 123 || keycode == 124)
		fdf->x_center = fdf->x_center + fdf->res * (keycode == 123 ? -1 : 1);
	if (keycode == 125 || keycode == 126)
		fdf->y_center = fdf->y_center + fdf->res *(keycode == 126 ? -1 : 1);
	if (keycode == 53)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		exit(0);
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	ft_draw_lines(fdf);
	return (1);
}

int			ft_draw(char *file)
{
	t_fdf	*fdf;

	if ((fdf = (ft_read(file))) == NULL)
		return (0);
	ft_add_mlx(fdf);
	ft_draw_lines(fdf);
	while (mlx_key_hook(fdf->win, &key_hook, fdf))
		mlx_loop(fdf->mlx);
	return (1);
}
