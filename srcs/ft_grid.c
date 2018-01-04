/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:44:36 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/04 13:11:42 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_del_fdf(t_fdf *fdf)
{
	int		y;
	int		x;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x)
		{
			ft_del_point(fdf->grid[y][x]);
			x++;
		}
		free(fdf->grid[y]);
		y++;
	}
	free(fdf->grid);
	free(fdf);
}

void	ft_res_fdf(t_fdf *fdf)
{
	int		y;
	int		x;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x)
		{
			fdf->grid[y][x]->x = x;
			fdf->grid[y][x]->y = y;
			fdf->grid[y][x]->color = 0;
			x++;
		}
		y++;
	}
}

t_fdf	*ft_ini_fdf(t_fdf *fdf, int y)
{
	int		x;

	x = 0;
	while (x < fdf->size_x)
	{
		if ((fdf->grid[y][x] = (t_point *)malloc(sizeof(t_point))) == NULL)
			return (NULL);
		fdf->grid[y][x]->x = x;
		fdf->grid[y][x]->y = y;
		fdf->grid[y][x]->color = 0;
		x++;
	}
	return (fdf);
}

t_fdf	*ft_map_fdf(t_fdf *fdf)
{
	ft_map_point(&ft_colr, fdf, 'c');
	ft_map_point(&ft_posx, fdf, 'x');
	ft_map_point(&ft_posy, fdf, 'y');
	return (fdf);
}

t_fdf	*ft_add_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, "FDF");
	return (fdf);
}
