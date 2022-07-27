/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:50:39 by ppajot            #+#    #+#             */
/*   Updated: 2022/06/20 17:09:00 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*initres(void)
{
	char	*result;

	result = (char *)malloc(1);
	if (!result)
		return (0);
	result[0] = 0;
	return (result);
}

char	*end_file(char *result, char currentl[BUFFER_SIZE + 1])
{	
	currentl[0] = 0;
	if (result[0] == 0)
	{
		free(result);
		return (0);
	}
	return (result);
}

int	read_endbuff(int fd, char buff[BUFFER_SIZE + 1])
{
	int	a;

	a = read(fd, buff, BUFFER_SIZE);
	if (a < 0)
		return (a);
	buff[a] = 0;
	return (a);
}

char	*free_res(char *result)
{
	free(result);
	return (0);
}
