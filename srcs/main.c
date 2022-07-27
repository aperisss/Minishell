/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:21:12 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/24 19:29:51 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(void)
{
	char *str;
	char *p = getenv("USER");
	char *prompt;

	prompt = ft_strjoin(p, "minishell$", "@");
	str = readline(prompt);
	while (str)
	{
		add_history(str);
		if (check_quote(str))
			lexer(str);
		free(str);
		str = readline(prompt);
	}
	free(prompt);
	free(p);
	return (0);
}
