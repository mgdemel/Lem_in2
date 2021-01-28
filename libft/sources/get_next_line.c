/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:01:51 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:00:46 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int			get_newline(char **s, char **line)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		if ((*line = ft_strsub(*s, 0, len)) == NULL)
			return (-1);
		if ((temp = ft_strdup(&((*s)[len + 1]))) == NULL)
			return (-1);
		free(*s);
		*s = temp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		if ((*line = ft_strdup(*s)) == NULL)
			return (-1);
		ft_strdel(s);
	}
	return (1);
}

static int			find_newline(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (0);
		s++;
	}
	if (*s == '\n')
		return (0);
	return (1);
}

static int			check_end(int ret, char **s, int fd, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
		return (get_newline(&s[fd], line));
}

/*
**	This function reads a string and places it in the buffer which can be used
**	by another function.
*/

int					get_next_line(const int fd, char **line)
{
	static char *s[4864];
	char		buff[BUFF_SIZE + 1];
	int			ret;
	char		*tmp;

	if (fd < 0 || line == NULL || fd > 4864)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] != NULL)
		{
			if ((tmp = ft_strjoin(s[fd], buff)) == NULL)
				return (-1);
			free(s[fd]);
			s[fd] = tmp;
		}
		else if ((s[fd] = ft_strdup(buff)) == NULL)
			return (-1);
		if (find_newline(s[fd]) == 0)
			break ;
	}
	return (check_end(ret, s, fd, line));
}
