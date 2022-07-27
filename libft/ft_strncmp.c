/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:11:06 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 19:01:21 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (i == n)
			return (0);
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}
