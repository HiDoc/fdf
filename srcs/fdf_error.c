/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:47:49 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/23 09:11:05 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_keycode(void)
{
	ft_putstr("Keycode mapping :\n\n");
	ft_putstr("c\t : Run random color (for maps where y < 25)\n");
	ft_putstr("t\t : Change top color\n");
	ft_putstr("b\t : Change bop color\n");
	ft_putstr("r\t : Reset\n");
	ft_putstr("up\t : move camera up\n");
	ft_putstr("down\t : move camera down\n");
	ft_putstr("left\t : move camera left\n");
	ft_putstr("rigth\t : move camera right\n");
	ft_putstr("+\t : zoom +\n");
	ft_putstr("-\t : zoom -\n");
	ft_putstr("w\t : not for epileptic...\n");
	ft_putstr("ESC\t : quit\n");
}

void	*fdf_error(int code, t_fdf *fdf)
{
	if (code == 1)
		ft_putstr("fdf : File format is invalid\n");
	else if (code == 2)
		ft_putstr("fdf : Allocation failed\n");
	else if (code == 3)
		perror("fdf ");
	else if (code == 4)
		perror("fdf ");
	else if (code == 5)
		ft_putstr("fdf : Allocation failed\n");
	else if (code == 6)
		perror("fdf ");
	else if (code == 7)
		perror("fdf ");
	else if (code == 8)
		ft_putstr("fdf : File is a directory or has no value\n");
	if (fdf != NULL)
		free(fdf);
	return (NULL);
}

void	fdf_usage(void)
{
	ft_putstr("Usage: fdf map_file.fdf\n");
}
