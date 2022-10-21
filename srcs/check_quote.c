/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:12:07 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/10 21:52:01 by ppajot           ###   ########.fr       */
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
		is_in_quote(*str, &quote, 0);
		if (*str == '(' && quote == 0)
			par++;
		else if (*str == ')' && quote == 0)
			par--;
		str++;
		if (par < 0)
			return (write (2, "closed an unopened parenthesis\n", 31), 0);
	}
	if (par)
		write (2, "parenthesis not closed\n", 24);
	if (quote)
		write (2, "quote not closed\n", 18);
	return (!par && !quote);
}

void	free_content(char *str)
{
	free(str);
}
