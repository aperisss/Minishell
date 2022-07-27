#include "minishell.h"

void    add_token(t_list**token_list)
{
    t_list*new_token;

    new_token = malloc(sizeof(t_token));

    if (*token_list)
    {
        new_token->next = *token_list;
        *token_list = new_token;
    }
    else
    {
        *token_list = new_token;
        new_token->next = NULL;
    }
}

void    create_token_list(t_list**token_list, char **cmd_table)
{
    int i;

    i = 0;
    while(cmd_table[i])
    {
        add_token(token_list);
        i++;
    }
}

void    tokenization2(t_list**token_list, char **cmd_table, int i)
{
    t_list*tmp;
    tmp = *token_list;

    while (cmd_table[i] && tmp)
    {
        if (ft_strcmp(cmd_table[i], "(") == 0)
            tmp->content.token_type = OPEN_PAR;
        else if (ft_strcmp(cmd_table[i], ")") == 0)
            tmp->content.token_type = CLOSE_PAR;
        else if (ft_strcmp(cmd_table[i], "&&") == 0)
            tmp->content.token_type = AND;
        else if (ft_strcmp(cmd_table[i], "||") == 0)
            tmp->content.token_type = OR;
        else
            tmp->content.token_type = WORDS;
        i++;
        tmp = tmp->next;
    }
}

void    tokenization(t_list**token_list, char **cmd_table)
{
    int i;
    t_list *tmp;
    tmp = *token_list;

    i = 0;
    while (cmd_table[i] && tmp)
    {
        if (ft_strcmp(cmd_table[i], "|") == 0)
            tmp->content.token_type = PIPE;
        else if (ft_strcmp(cmd_table[i], ">") == 0)
            tmp->content.token_type = RET_TO;
        else if (ft_strcmp(cmd_table[i], "<") == 0)
            tmp->content.token_type = RET_FROM;
        else if (ft_strcmp(cmd_table[i], ">>") == 0)
            tmp->content.token_type = DGREAT;
        else if (ft_strcmp(cmd_table[i], "<<") == 0)
            tmp->content.token_type = DLESS;
        else
            tokenization2(&tmp,cmd_table, i);
        i++;
        tmp = tmp->next;
    }
}

t_list *lexer(char *input)
{
    int i;
    char **cmd_table;
    t_list*token_list;

    token_list = malloc(sizeof(t_token));
    token_list = NULL;
    cmd_table = ft_split(input, ' ');
    create_token_list(&token_list, cmd_table);
    tokenization(&token_list, cmd_table);
    return (token_list);
}