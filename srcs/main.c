/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 13:32:12 by fmadura           #+#    #+#             */
/*   Updated: 2018/03/16 13:31:54 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_error(void)
{
	ft_putstr("Usage: fdf map_file.fdf");
}

int			main(int argc, char **argv)
{
	if (argc > 1 && argc == 2)
	{
		if (!(fdf_draw(argv[1])))
			perror("Error ");
	}
	else
		ft_error();
	return (0);
}
