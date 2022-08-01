#include "minishell.h"

int check_op(t_list **token_list)
{
	if ((*token_list)->content.token_type == PIPE 
		|| (*token_list)->content.token_type == AND
		|| (*token_list)->content.token_type == OR)
		return (1);
	return (0);
}

int check_redir(t_list **token_list)
{
	if ((*token_list)->content.token_type == RET_FROM 
		|| (*token_list)->content.token_type == RET_TO
		|| (*token_list)->content.token_type == DLESS
		|| (*token_list)->content.token_type == DGREAT)
		return (1);
	return (0);
}

t_list  *ft_listlast(t_list *stack)
{
	while (stack && stack->next != NULL)
		stack = stack->next;
	return (stack);
}

void    ft_lstadd_back(t_list **list, int token)
{
	t_list  *new;
	new = malloc(sizeof(t_list));
	new->next = NULL;
	new->content.token_type = token;
	if (*list)
		ft_listlast(*list)->next = new;
	else
		*list = new;
}

void    shift(t_list **stack_list, t_list **token_list)
{
	t_list *tmp;

	if (!*token_list)
		return ;
	if (*stack_list)
		ft_listlast(*stack_list)->next = *token_list;
	else
		*stack_list = *token_list;
	tmp = (*token_list)->next;
	(*token_list)->next = 0;
	*token_list =  tmp;
}
