/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/11 15:13:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_pos(int x, int y)
{
	return ((x * 20 + 200) + (y * 20));
}

int		ft_pythagore(int a, int b)
{
	return ((int)sqrt(pow(a, 2) + pow(b, 2)));
}

int		ft_draw(char *file)
{
	void	*mlx;
	void	*win;
	t_grid	*grid;
	int		x;
	int		y;
	int		tmp;
	int		tmp2;
	int		pas;
	int		distance;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 800, "FDF");
	if ((grid = (ft_read(file))) == NULL)
		return (0);
	y = 0;
	distance = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			// Remplit les carres
			if (x + 1 < grid->size_x && y + 1 < grid->size_y)
			{
				if (grid->grid[y][x] == grid->grid[y][x + 1] && grid->grid[y][x] == grid->grid[y + 1][x]
					&& grid->grid[y + 1][x + 1] == grid->grid[y][x])
				{
					tmp = 0;
					while (tmp < (ft_pos(y + 1, 0) - ft_pos(y, 0)))
					{
						tmp2 = 0;
						while (tmp2 < (ft_pos(x + 1, y) - ft_pos(x, y)))
						{
							mlx_pixel_put(mlx, win,
								ft_pos(x, y) + tmp + tmp2, 
								ft_pos(y - grid->grid[y][x], 0) + tmp2 + 100,
								0x00222222);
							tmp2++;
						}
						tmp++;
					}
				}
				else	
				{
					tmp = 0;
					while (tmp < (ft_pos(y + 1, 0) - ft_pos(y, 0)))
					{
						tmp2 = 0;
						while (tmp2 < (ft_pos(x + 1, y) - ft_pos(x, y)))
						{
							mlx_pixel_put(mlx, win,
								ft_pos(x, y) + tmp + tmp2, 
								ft_pos(y - grid->grid[y][x], 0) + tmp2 + 100,
								0x0000FF00);
							tmp2++;
						}
						tmp++;
					}
				}
			}
			tmp = 0;
			tmp2 = 0;
			pas = 0;
			// Remplit de facon horizontale
			if (x + 1 < grid->size_x)
			{
				distance = ft_pos(x + 1, y) - ft_pos (x, y);
				if (grid->grid[y][x] == grid->grid[y][x + 1])
					while (tmp < distance)
					{
						mlx_pixel_put(mlx, win,
								ft_pos(x, y) + tmp, 
								ft_pos(y - grid->grid[y][x], 0) + 100,
								0x00992255);
						tmp++;
					}
				else
				{
					distance = ft_pythagore(
							ft_pos(x + 1, y) - ft_pos (x, y),
							(ft_pos(y - grid->grid[y][x + 1], 0) - ft_pos(y - grid->grid[y][x], 0)));
					while (tmp < distance)
							//&&
							//ft_pos(y - grid->grid[y][x], 0) - (grid->grid[y][x] > grid->grid[y][x + 1] ? -tmp : tmp)
							//!= ft_pos(y - grid->grid[y][x + 1],0))
					{
						pas = distance / 20;
						mlx_pixel_put(mlx, win,
								ft_pos(x, y) + tmp2, 
								ft_pos(y - grid->grid[y][x], 0) - (grid->grid[y][x] > grid->grid[y][x + 1] ? -tmp : tmp) + 100,
								0x00662255);
						tmp++;
						tmp2 += tmp % pas == 0; 
					}
				}
			}
			tmp = 0;
			tmp2 = 0;
			pas = 0;
			// Remplit de facon verticale
			if (y + 1 < grid->size_y)
			{
				distance = ft_pos(y + 1, 0) - ft_pos (y, 0);
				if (grid->grid[y][x] == grid->grid[y + 1][x])
					while (tmp < distance)
					{
						mlx_pixel_put(mlx, win,
								ft_pos(x, y) + tmp,
								ft_pos(y - grid->grid[y + 1][x], 0) + tmp + 100,
								0x00551199);
						tmp++;
					}
				else
				{
					distance = ft_pythagore(ft_pos(y + 1 - grid->grid[y + 1][x], 0) - ft_pos(y - grid->grid[y][x], 0), ft_pos(x, y + 1) - ft_pos(x, y));
					while (tmp < distance)
					{
						pas = distance / 20;
						mlx_pixel_put(mlx, win,
								ft_pos(x, y) + tmp2, 
								ft_pos(y - grid->grid[y][x], 0) - (grid->grid[y][x] > grid->grid[y + 1][x] ? -tmp : tmp) + 100,
								0x00111199);
						tmp++;
						tmp2 += tmp % pas == 0; 
					}
				}
			}
			mlx_pixel_put(mlx, win, ft_pos(x, y), ft_pos(y - grid->grid[y][x], 0) + 100, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	ft_del_grid(grid);
	mlx_loop(mlx);
	return (1);
}
