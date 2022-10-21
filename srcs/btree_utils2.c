/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:03:29 by aperis            #+#    #+#             */
/*   Updated: 2022/09/09 19:40:57 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_op(t_list **token_list)
{
	t_token	*token;

	token = (*token_list)->content;
	if (token->token_type == PIPE
		|| token->token_type == AND
		|| token->token_type == OR)
		return (1);
	return (0);
}

int	check_redir(t_list **token_list)
{
	t_token	*token;

	token = (*token_list)->content;
	if (token->token_type == RET_FROM
		|| token->token_type == RET_TO
		|| token->token_type == DLESS
		|| token->token_type == DGREAT)
		return (1);
	return (0);
}

t_list	*ft_listlast(t_list *stack)
{
	while (stack && stack->next != NULL)
		stack = stack->next;
	return (stack);
}

void	init_r(t_list **tl, t_list **st, t_list **s)
{
	*tl = *s;
	*st = *s;
	if ((*s)->next)
		*s = (*s)->next;
}

void	init_token(t_token **t, t_token **t2, t_list *stack, t_list *sless)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *t;
	tmp2 = *t2;
	*t = tmp;
	*t2 = tmp2;
	*t = stack->content;
	*t2 = sless->content;
}
