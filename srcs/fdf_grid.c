/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:40:06 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/05 13:40:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_del_grid(t_fdf *fdf)
{
	int		y;
	int		x;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			ft_del_point(fdf->grid[y][x]);
			x++;
		}
		free(fdf->grid[y]);
		y++;
	}
	free(fdf->grid);
}

void	ft_res_grid(t_fdf *fdf)
{
	int		y;
	int		x;

	y = 0;
	while (y < fdf->size_y)
	{
		x = 0;
		while (x < fdf->size_x[y])
		{
			fdf->grid[y][x]->x = x;
			fdf->grid[y][x]->y = y;
			fdf->grid[y][x]->color = 0;
			x++;
		}
		y++;
	}
	ft_ini_fdf(fdf, 20);
}

t_fdf	*ft_ini_line(t_fdf *fdf, int y)
{
	int		x;

	x = 0;
	while (x < fdf->size_x[y])
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