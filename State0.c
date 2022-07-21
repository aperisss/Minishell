#include "minishell.h"

void    state0(t_stack *stack, t_token *token_list)
{
    if(stack->type_stack == OPERATEUR_SEQUENCE)
        state2(stack, token_list);
    if (token_list->token == OPEN_PAR)
    {
        shift(stack, token_list);
        state1(stack, token_list);
    }
    else
        state3(stack, token_list); 
}