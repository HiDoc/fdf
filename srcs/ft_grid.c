/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:44:36 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/10 15:36:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_del_grid(t_grid *grid)
{
	int		y;

	y = 0;
	while (y < grid->size_y)
	{
		free(grid->grid[y]);
		y++;
	}
	free(grid->grid);
	free(grid);
}

t_grid	*ft_new_grid(int **tab, int size_x, int size_y)
{
	t_grid	*new;

	if ((new = (t_grid *)malloc(sizeof(t_grid))) == NULL)
		return (NULL);
	new->grid = tab;
	new->size_x = size_x;
	new->size_y = size_y;
	return (new);
}
