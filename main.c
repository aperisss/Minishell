#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *input;
    input = NULL;
    t_token *token_list;
    while (1)
    {
        input = readline("$>");
        if (input)
        {
            token_list = lexer(input);
            parsing(token_list);
            return (0);
        }
    }
}
