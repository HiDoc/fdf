/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:46:30 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/13 14:16:48 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_parse_line(int y, t_grid *grid, char *str, int filled)
{
	int		count;
	int		x;
	int		z;

	count = 0;
	x = 0;
	while (str[count])
	{
		z = ft_atoi(&str[count]);
		if (filled)
			(grid->grid[y][x])->z = z;
		while (str[count] && (ft_isdigit(str[count]) || str[count] == '-'))
			count++;
		while (str[count] && !(ft_isdigit(str[count])))
			count++;
		x++;
	}
	if (!filled)
	{
		grid->size_x = x;
		if ((grid->grid[y] = (t_point **)malloc(sizeof(t_point *) * x)) == NULL)
			return (0);
		ft_ini_grid(grid, y);
		return (ft_parse_line(y, grid, str, 1));
	}
	return (1);
}

int		ft_parse_file(int fd, t_grid *grid, int sized)
{
	char	**line;
	t_point	***tab;
	int		y;
	int		x;

	x = 0;
	y = 0;
	line = (char **)malloc(sizeof(char *));
	while (get_next_line(fd, line) > 0)
	{
		if (sized)
			ft_parse_line(y, grid, *line, 0);
		free(*line);
		y++;
	}
	free(line);
	if (!sized)
	{
		if ((tab = (t_point ***)malloc(sizeof(t_point **) * y)) == NULL)
			return (0);
		grid->grid = tab;
		grid->size_y = y;
	}
	return (1);
}

t_grid	*ft_read(char *file)
{
	int		fd;
	t_grid	*new;

	if ((new = (t_grid *)malloc(sizeof(t_grid))) == NULL)
		return (NULL);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if(!(ft_parse_file(fd, new, 0)))
		return (NULL);
	if (close(fd) == -1 || (fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(ft_parse_file(fd, new, 1)))
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	return (new);
}
