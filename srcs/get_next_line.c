/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:58:27 by fmadura           #+#    #+#             */
/*   Updated: 2017/12/07 14:43:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*substract(char *store, char **line)
{
	char	*tmp;

	*line = ft_strsub(store, 0, ft_strchri(store, '\n'));
	tmp = ft_strsub(store, ft_strchri(store, '\n') + 1, ft_strlen(store));
	free(store);
	store = ft_strdup(tmp);
	free(tmp);
	return (store);
}

static char	*join(char *store, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(store, buff);
	if (*store)
	{
		free(store);
		store = NULL;
	}
	store = ft_strdup(tmp);
	free(tmp);
	return (store);
}

int			get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static char	*store[3000];

	if (!(line))
		return (-1);
	if (fd > -1 && store[fd] && ft_strchri(store[fd], '\n') != -1)
	{
		store[fd] = substract(store[fd], line);
		return (1);
	}
	if ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		store[fd] = ((!store[fd]) ? ft_strdup(buff) : join(store[fd], buff));
		return (get_next_line(fd, line));
	}
	if (ret == 0 && store[fd] && store[fd][0])
	{
		*line = ft_strdup(store[fd]);
		free(store[fd]);
		store[fd] = NULL;
		return (1);
	}
	return (ret > 0 ? 1 : ret);
}
