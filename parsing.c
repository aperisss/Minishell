#include "minishell.h"



int parse_par(t_list *token_list)
{
    t_list *prev;
    int open;
    int close;

    open = 0;
    close = 0;
    prev = token_list;
    token_list = token_list->next;
    if (prev->content.token_type == CLOSE_PAR)
        close++;
    if (prev->content.token_type == OPEN_PAR)
        open++;
    while (token_list)
    {
        if (prev->content.token_type == OPEN_PAR
            && token_list->content.token_type == CLOSE_PAR)
                return (0);
        if (token_list->content.token_type == OPEN_PAR)
            open++;
        if (token_list->content.token_type == CLOSE_PAR)
            close++;
        token_list = token_list->next;
        prev = prev->next;
    }
    if (open != close)
        return (0);
    return (1);
}

int parsing( t_list *token_list)
{
    t_list *prev;

    if (check_op(&token_list))
        return (0);
    if (!parse_par(token_list))
        return (0);
    prev = token_list;
    token_list = token_list->next;
    while (token_list)
    {
        if ((!check_op(&prev) && prev->content.token_type != OPEN_PAR)
             && token_list->content.token_type == OPEN_PAR)
            return (0);
        if ((!check_op(&token_list) && token_list->content.token_type != CLOSE_PAR)
            && prev->content.token_type == CLOSE_PAR)
            return (0);
        if (check_redir(&prev) && token_list->content.token_type != WORDS)
            return (0);
        if (check_op(&prev) && check_op(&token_list))
            return (0);
        prev = prev->next;
        token_list=token_list->next;
    }
    if (check_op(&prev) || check_redir(&prev))
        return (0);
    return (1);
}