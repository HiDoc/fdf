/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:40:23 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/23 09:09:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_is_file_valid(char *str)
{
	int count;

	count = (int)ft_strlen(str);
	if (count < 5)
		return (0);
	if (ft_strncmp(&str[count - 4], ".fdf", 4) != 0)
		return (0);
	return (1);
}

static int	fdf_next_int(int count, char *str)
{
	while (str[count] && (ft_isdigit(str[count]) || str[count] == '-'))
		count++;
	while (str[count] && !(ft_isdigit(str[count])))
		count++;
	return (count);
}

static int	fdf_parse_line(int y, t_fdf *fdf, char *str, int filled)
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
		count = fdf_next_int(count, str);
		x++;
	}
	if (!filled)
	{
		fdf->size_x[y] = x;
		if (!(fdf->grid[y] = (t_point **)malloc(sizeof(t_point *) * x)))
			return (0);
		fdf_ini_line(fdf, y);
		return (fdf_parse_line(y, fdf, str, 1));
	}
	return (1);
}

static int	fdf_parse_file(int fd, t_fdf *fdf, int sized, int y)
{
	char	*line;
	t_point	***tab;
	int		x;

	x = 0;
	line = NULL;
	tab = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (sized && !(fdf_parse_line(y, fdf, line, 0)))
			return (0);
		free(line);
		line = NULL;
		y++;
	}
	if (!sized)
	{
		if (!(y) || ((tab = (t_point ***)malloc(sizeof(t_point **) * y)) ==
		NULL) || ((fdf->size_x = (int *)malloc(sizeof(int) * y)) == NULL))
			return (0);
		fdf->grid = tab;
		fdf->size_y = y;
	}
	return (1);
}

t_fdf		*fdf_read(char *file)
{
	int		fd;
	t_fdf	*new;

	new = NULL;
	if (!(fdf_is_file_valid(file)))
		return (fdf_error(1, new));
	if ((new = (t_fdf *)malloc(sizeof(t_fdf))) == NULL)
		return (fdf_error(2, new));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (fdf_error(3, new));
	if (!(fdf_parse_file(fd, new, 0, 0)))
		return (fdf_error(4, new));
	if (close(fd) == -1 || (fd = open(file, O_RDONLY)) == -1)
		return (fdf_error(5, new));
	if (!(fdf_parse_file(fd, new, 1, 0)))
		return (fdf_error(6, new));
	if (close(fd) == -1)
		return (fdf_error(7, new));
	if (!(fdf_no_value(new)))
		return (fdf_error(8, new));
	fdf_ini_fdf(new, 40);
	return (new);
}
