/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:23:24 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 18:08:12 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_token(t_list *token_list)
{
	t_list	*current;
	t_token	*token;

	current = token_list;
	while (current)
	{
		token = (t_token *)current->content;
		if (is_op(token->string[0]) && ft_strlen(token->string) > 2)
			return (0);
		if (token->string[0] == '&' && !token->string[1])
			return (0);
		current = current->next;
	}
	return (1);
}

int	token_syntax(int prev, int current)
{
	if (prev > 0 && prev < 5 && current != WORDS)
		return (0);
	if (current == OPEN_PAR && prev != -1 && prev != OR && prev != AND
		&& prev != OPEN_PAR)
		return (0);
	if (prev == CLOSE_PAR && current != AND && current != OR
		&& current != CLOSE_PAR)
		return (0);
	if (current == PIPE && prev != WORDS)
		return (0);
	if (prev == PIPE && !(current >= 0 && current <= 4))
		return (0);
	if (prev == OPEN_PAR && current == CLOSE_PAR)
		return (0);
	if (prev == -1 && (current == AND || current == OR))
		return (0);
	return (1);
}

int	check_syntax(t_list *token_list)
{
	t_list	*current;
	t_token	*token;
	int		prev_token;

	prev_token = -1;
	current = token_list;
	if (!current)
		return (1);
	while (current)
	{
		token = (t_token *)current->content;
		if (!token_syntax(prev_token, token->token_type))
			return (write (2, "syntax error near unexpected token '", 36)
				, write (2, token->string,
					ft_strlen(token->string)), write (2, "'\n", 3), 0);
		prev_token = token->token_type;
		current = current->next;
	}
	if (prev_token != WORDS && prev_token != CLOSE_PAR)
		return (write (2, "syntax error near unexpected token ", 35)
			, write (2, "newline\n", 9), 0);
	return (1);
}

t_list	*lexer(char *input, t_data *data)
{
	t_list	*token_list;
	char	*temp;

	token_list = 0;
	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!temp || !*input)
		return (free(temp), (void *)0);
	if (!tokener(input, &token_list, temp))
	{
		ft_lstclear(&token_list, &free_token);
		exit_error(0, data, -1, 0);
	}
	free(temp);
	if (!check_token(token_list))
	{
		write(2, "Invalid token\n", 14);
		g_exit_status = 2;
		return (ft_lstclear(&token_list, &free_token), (void *)0);
	}	
	if (!check_syntax(token_list))
	{
		g_exit_status = 2;
		return (ft_lstclear(&token_list, &free_token), (void *)0);
	}
	return (token_list);
}
