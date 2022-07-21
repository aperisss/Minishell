#include "minishell.h"

t_stack  *ft_stacklast(t_stack *stack)
{
        while (stack && stack->next != NULL)
                stack = stack->next;
        return (stack);
}


void    ft_lstadd_back(t_stack **stack, t_token_type token)
{
    t_stack *new;
    new = malloc(sizeof(t_stack));
    new->next = NULL;
    new->type_stack = token;
        if (*stack)
                ft_stacklast(*stack)->next = new;
        else
                *stack = new;
}

void    reduce(t_stack *stack_list, t_token_type token, t_token *token_list, int nb_reduce)
{
    t_stack *reduce;
    reduce = malloc(sizeof(t_stack));
    reduce->next = NULL;
    reduce->type_stack = token;
    if (nb_reduce == 1)
    {
        while(stack_list->next != NULL)
            stack_list = stack_list->next;
    }
    else
    {
        while(stack_list->next->next != NULL)
            stack_list = stack_list->next;
    }
    stack_list->next = reduce;
    state0(stack_list, token_list);
}
void    shift(t_stack *stack_list, t_token *token_list)
{
    ft_lstadd_back(&stack_list, token_list->token);
    token_list = token_list->next;
}

int parsing(t_token *token_list)
{
    t_stack *stack;

    stack = NULL;
    stack = malloc(sizeof(stack));
    state0(stack, token_list);
}