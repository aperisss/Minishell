/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:40:24 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/03 19:13:36 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb * size / size != nmemb)
		return (0);
	res = malloc(nmemb * size);
	if (!res)
		return (0);
	return (ft_memset(res, 0, nmemb * size));
}
