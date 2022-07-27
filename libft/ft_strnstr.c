/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:08:26 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 18:49:39 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	n = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (big[n] && n < len)
	{
		i = 0;
		while (big[i + n] == little[i] && little[i] != 0 && i + n < len)
			i++;
		if (little[i] == 0)
			return ((char *)(big + n));
		n++;
	}
	return (0);
}
