/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:46:30 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/04 15:24:50 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_next_int(int count, char *str)
{
	while (str[count] && (ft_isdigit(str[count]) || str[count] == '-'))
		count++;
	while (str[count] && !(ft_isdigit(str[count])))
		count++;
	return (count);
}

int			ft_parse_line(int y, t_fdf *fdf, char *str, int filled)
{
	int		count;
	int		x;
	int		z;

	count = 0;
	x = 0;
	while (str[count] && ft_isspace(str[count]))
		count++;
	while (str[count])
	{
		z = ft_atoi(&str[count]);
		if (filled)
			(fdf->grid[y][x])->z = z;
		count = ft_next_int(count, str);
			x++;
	}
	if (!filled)
	{
		fdf->size_x[y] = x;
		if ((fdf->grid[y] = (t_point **)malloc(sizeof(t_point *) * x)) == NULL)
			return (0);
		ft_ini_fdf(fdf, y);
		return (ft_parse_line(y, fdf, str, 1));
	}
	return (1);
}

int			ft_parse_file(int fd, t_fdf *fdf, int sized)
{
	char	*line;
	t_point	***tab;
	int		y;
	int		x;

	x = 0;
	y = 0;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (sized)
			ft_parse_line(y, fdf, line, 0);
		free(line);
		y++;
	}
	line = NULL;
	if (!sized)
	{
		if (((tab = (t_point ***)malloc(sizeof(t_point **) * y)) == NULL)
		|| ((fdf->size_x = (int *)malloc(sizeof(int) * y)) == NULL))
			return (0);
		fdf->grid = tab;
		fdf->size_y = y;
	}
	return (1);
}

t_fdf		*ft_read(char *file)
{
	int		fd;
	t_fdf	*new;

	if ((new = (t_fdf *)malloc(sizeof(t_fdf))) == NULL)
		return (NULL);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(ft_parse_file(fd, new, 0)))
		return (NULL);
	if (close(fd) == -1 || (fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if (!(ft_parse_file(fd, new, 1)))
		return (NULL);
	if (close(fd) == -1)
		return (NULL);
	ft_map_fdf(new);
	ft_add_mlx(new);
	return (new);
}
