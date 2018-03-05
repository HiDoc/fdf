/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:39:48 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 13:46:39 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_draw_line_xd(t_fdf *fdf, t_point *p1, t_point *p2)
{
	int		i;
	int		coef;
	int		cmp;
	int 	color;
	float	percent;

	i = 0;
	cmp = p1->z - p2->z;
	coef = ft_coef(fdf, p1, p2);
	while (i < fdf->res * coef)
	{
		percent = ((float)i / (float)coef) / (float)fdf->res;
		color = ft_color_mixer(p1->color, p2->color, percent);
		if (!(cmp))
			ft_pix_put_color(fdf, p1->x + i, p1->y + (p1->y == p2->y ? 0 : i), color);
		else if (cmp > 0)
			ft_pix_put_color(fdf, p1->x + i / coef, p1->y + i, color);
		else 
			ft_pix_put_color(fdf, 
					p1->x + i / coef, p1->y - (p1->y == p2->y ? 0 : i), color);
		i++;
	}
}

static int	ft_draw_lines_xd(t_fdf *fdf)
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
				ft_draw_line_xd(fdf, a, fdf->grid[y][x + 1]);
			if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				ft_draw_line_xd(fdf, a, fdf->grid[y + 1][x]);
			x++;
			mlx_do_sync(fdf->mlx);
		}
		y++;
	}
	return (1);
}

static void	ft_draw_line(t_fdf *fdf, t_point *p1, t_point *p2)
{
	int		i;
	int		coef;
	int		cmp;
	int 	color;
	float	percent;

	i = 0;
	cmp = p1->z - p2->z;
	coef = ft_coef(fdf, p1, p2);
	while (i < fdf->res * coef)
	{
		percent = ((float)i / (float)coef) / (float)fdf->res;
		color = ft_color_mixer(p1->color, p2->color, percent);
		if (!(cmp))
			ft_pix_put_color(fdf, p1->x + i, p1->y + (p1->y == p2->y ? 0 : i), color);
		else if (cmp > 0)
			ft_pix_put_color(fdf, p1->x + i / coef, p1->y + i, color);
		else 
			ft_pix_put_color(fdf, 
					p1->x + i / coef, p1->y - (p1->y == p2->y ? 0 : i), color);
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
				ft_draw_line(fdf, a, fdf->grid[y][x + 1]);
			if (y + 1 < fdf->size_y && x < fdf->size_x[y + 1])
				ft_draw_line(fdf, a, fdf->grid[y + 1][x]);
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
	if (keycode == 8)
	{
		fdf->rand = ft_random(fdf->rand);
		ft_map_point(&ft_rncg, fdf, 'c');
	}
	else 
	{
		if (keycode == 69 || keycode == 78)
		{
			fdf->res = fdf->res + (keycode == 78 ? -1 : 1);
			if (fdf->res < 1)
				fdf->res = 1;
			ft_map_point(&ft_posx, fdf, 'x');
			ft_map_point(&ft_posy, fdf, 'y');
			ft_max_y(fdf);
			ft_max_x(fdf);
			fdf->x_center = fdf->x_win / 2 - fdf->x_end /2 ;
			fdf->y_center = abs(fdf->y_start) + fdf->y_win / 2
				- (fdf->y_end - fdf->y_start) / 2;
		}
		if (keycode == 15)
			ft_res_grid(fdf);
		if (keycode == 123 || keycode == 124)
			fdf->x_center = fdf->x_center + fdf->res * (keycode == 123 ? 1 : -1);
		if (keycode == 125 || keycode == 126)
			fdf->y_center = fdf->y_center + fdf->res *(keycode == 126 ? 1 : -1);
		if (keycode == 53)
		{
			mlx_clear_window(fdf->mlx, fdf->win);
			exit(0);
		}
		mlx_clear_window(fdf->mlx, fdf->win);
	}
	ft_draw_lines_xd(fdf);
	return (1);
}

int			ft_draw(char *file)
{
	t_fdf	*fdf;

	if ((fdf = (ft_read(file))) == NULL)
		return (0);
	ft_add_mlx(fdf);
	ft_draw_lines(fdf);
	fdf->rand = ft_random((int)&fdf->rand);
	while (mlx_key_hook(fdf->win, &key_hook, fdf))
		mlx_loop(fdf->mlx);
	return (1);
}
