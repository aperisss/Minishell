/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:50:36 by ppajot            #+#    #+#             */
/*   Updated: 2022/06/20 17:12:23 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pushback(char currentl[BUFFER_SIZE + 1],
			char line[BUFFER_SIZE + 1], int newbegin)
{
	int	i;

	i = 0;
	while (line[i + newbegin])
	{
		currentl[i] = line[i + newbegin];
		i++;
	}
	currentl[i] = 0;
}

char	*cat_alloc(char newend[BUFFER_SIZE + 1], char *oldres, int size)
{
	int		i;
	char	*newres;

	i = -1;
	newres = (char *)malloc(size + ft_strlen(oldres) + 1);
	if (!newres)
		return (0);
	while ((size_t)++i < ft_strlen(oldres))
		newres[i] = oldres[i];
	i = -1;
	while (++i < size)
		newres[i + ft_strlen(oldres)] = newend[i];
	newres[size + ft_strlen(oldres)] = 0;
	free(oldres);
	return (newres);
}

int	nextendl(char line[BUFFER_SIZE + 1])
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	checkendl(char currentl[BUFFER_SIZE + 1], char line[BUFFER_SIZE + 1],
			char **result)
{
	int	a;

	a = nextendl(line);
	if (a >= 0)
	{
		*result = cat_alloc(line, *result, a + 1);
		pushback(currentl, line, a + 1);
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	currentl[BUFFER_SIZE + 1];
	char		buff[BUFFER_SIZE + 1];
	char		*result;
	int			a;

	result = initres();
	if (!result)
		return (0);
	if (fd < 0)
		return (free_res(result));
	if (checkendl(currentl, currentl, &result))
		return (result);
	result = cat_alloc(currentl, result, ft_strlen(currentl));
	a = read_endbuff(fd, buff);
	while (a)
	{
		if (a < 0)
			return (free_res(result));
		if (checkendl(currentl, buff, &result))
			return (result);
		result = cat_alloc(buff, result, a + 1);
		a = read_endbuff(fd, buff);
	}
	return (end_file(result, currentl));
}
/*
#include <fcntl.h>
#include <stdio.h>
int	main()
{
	int i = 0;
	char *s;
	int fd1 = open ("big_line_no_nl", 0);
	//int fd2 = open ("test", 0);
	while (i < 130)
	{
		s = get_next_line(fd1);
		printf("%s", s);
		free(s);
	//	s = get_next_line(fd2);
		//printf("%s", s);
		//free(s);
		i++;
	}
	close(fd1);
	//close(fd2);
}*/