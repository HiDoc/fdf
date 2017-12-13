/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:44:36 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 14:36:32 by fmadura          ###   ########.fr       */
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

void	ft_ini_grid(t_grid *grid, int y)
{
	int x;

	x = 0;
	while (x < grid->size_x)
	{
		if ((grid->grid[y][x] = (t_point *)malloc(sizeof(t_point))) == NULL)
			return ;
		(grid->grid[y][x])->x = x;
		(grid->grid[y][x])->y = y;
		x++;
	}
}

t_grid	*ft_new_grid(t_point ***tab, int size_x, int size_y)
{
	t_grid	*new;

	if ((new = (t_grid *)malloc(sizeof(t_grid))) == NULL)
		return (NULL);
	new->grid = tab;
	new->size_x = size_x;
	new->size_y = size_y;
	return (new);
}
