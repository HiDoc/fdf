/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/12 16:22:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
# define RES 20

int		ft_posy(t_grid *grid, int x, int y)
{
	return (real_y(grid, x, y) * RES + 400);
}

int		ft_posx(int x, int y)
{
	return ((x * RES + 200) + (y * RES));
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
	win = mlx_new_window(mlx, 1000, 1000, "FDF");
	if ((grid = (ft_read(file))) == NULL)
		return (0);
	y = 0;
	distance = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			tmp = 0;
			tmp2 = 0;
			pas = 0;
			// Remplit de facon horizontale
			if (x + 1 < grid->size_x)
			{
				distance = ft_pythagore(ft_posx(x + 1, y) - ft_posx(x, y), (ft_posy(grid, x + 1, y) - ft_posy(grid, x, y)));
				while (tmp < distance)
				{
					pas = distance / RES;
					if (grid->grid[y][x] == grid->grid[y][x + 1])
					{
						mlx_pixel_put(mlx, win, ft_posx(x, y) + tmp, ft_posy(grid, x, y), 0x00BB0000);
					}
					else
						mlx_pixel_put(mlx, win, ft_posx(x, y) + tmp2, 
						ft_posy(grid, x, y) + (grid->grid[y][x] > grid->grid[y][x + 1] ? tmp : -tmp), 0x00AA22AA);
					tmp++;
					tmp2 += tmp % pas == 0; 
				}
			}
			tmp = 0;
			tmp2 = 0;
			pas = 0;
			// Remplit de facon verticale
			if (y + 1 < grid->size_y)
			{
				distance = ft_pythagore(ft_posy(grid, x, y + 1) - ft_posy(grid, x, y), ft_posx(x, y + 1) - ft_posx(x, y));
				ft_putstr("y + 1:");
				ft_putendl(ft_itoa(ft_posy(grid, x, y + 1)));
				ft_putstr("y :");
				ft_putendl(ft_itoa(ft_posy(grid, x, y)));
				ft_putstr("x + 1 :");
				ft_putendl(ft_itoa(ft_posx(x, y + 1)));
				ft_putstr("x :");
				ft_putendl(ft_itoa(ft_posx(x, y)));
				ft_putendl(ft_itoa(distance));
				while (tmp < distance)
				{
					pas = distance / RES;
					if (grid->grid[y][x] == grid->grid[y + 1][x])
						mlx_pixel_put(mlx, win, ft_posx(x, y) + tmp2, ft_posy(grid, x, y) + tmp, 0x000000BB);
					else
						mlx_pixel_put(mlx, win, ft_posx(x, y) + tmp2, ft_posy(grid, x, y) -
						(grid->grid[y][x] > grid->grid[y + 1][x] ? -tmp : tmp),
						0x00BB0000);
					tmp++;
					tmp2 += tmp % pas == 0; 
				}
			}
			mlx_pixel_put(mlx, win, ft_posx(x, y), ft_posy(grid, x, y), 0x00FFFFFF);
			x++;
		}
		y++;
	}
	ft_del_grid(grid);
	mlx_loop(mlx);
	return (1);
}
