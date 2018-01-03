/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:44:36 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/03 18:51:45 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_del_grid(t_grid *grid)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			ft_del_point(grid->grid[y][x]);
			x++;
		}
		free(grid->grid[y]);
		y++;
	}
	free(grid->grid);
	free(grid);
}

void	ft_res_grid(t_grid *grid)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			grid->grid[y][x]->x = x;
			grid->grid[y][x]->y = y;
			grid->grid[y][x]->color = 0;
			x++;
		}
		y++;
	}
}

t_grid	*ft_ini_grid(t_grid *grid, int y)
{
	int		x;

	x = 0;
	while (x < grid->size_x)
	{
		if ((grid->grid[y][x] = (t_point *)malloc(sizeof(t_point))) == NULL)
			return (NULL);
		grid->grid[y][x]->x = x;
		grid->grid[y][x]->y = y;
		grid->grid[y][x]->color = 0;
		x++;
	}
	return (grid);
}

t_grid	*ft_map_grid(t_grid *grid)
{
	ft_map_point(&ft_colr, grid, 'c');
	ft_map_point(&ft_posx, grid, 'x');
	ft_map_point(&ft_posy, grid, 'y');
	return (grid);
}

t_grid	*ft_add_mlx(t_grid *grid)
{
	grid->mlx = mlx_init();
	grid->win = mlx_new_window(grid->mlx, 1000, 1000, "FDF");
	return (grid);
}
