/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:12:07 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/24 23:23:37 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *str)
{
	int	par;
	int	quote;

	par = 0;
	quote = 0;
	while (*str)
	{
		if (*str == '\'' && quote == 0)
			quote = 1;
		if (*str == '\'' && quote == 1)
			quote = 0;
		if (*str == '\"' && quote == 0)
			quote = 2;
		if (*str == '\"' && quote == 2)
			quote = 0;
		if (*str == '(' && quote == 0)
			par++;
		if (*str == ')' && quote == 0)
			par--;
		str++;
		if (par < 0)
			return (0);
	}
	return (!par && !quote);
}