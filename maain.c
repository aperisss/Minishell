#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *input;
    t_btree *ast;
    t_data data;
    t_btree *tmp;
    t_btree *tmp2;
    t_btree *tmp3;
    input = NULL;
    data.par = 0;
    t_list *token_list;
    while (1)
    {
        input = readline("$>");
        if (input)
        {
            token_list = lexer(input);
            if (parsing(token_list) == 0)
            {
                printf("erreur parsing token_list\n");
                return (0);
            }
            while (token_list->content.token_type == OPEN_PAR)
                 token_list = token_list->next;
            ast = btree_create(&token_list, &data, 0);
            tmp = ast;
            while(ast)
            {
                printf ("ast = %d \n", ast->content.token_type);
                ast = ast->left;
            }
            printf("\n");
            ast = tmp->right;
            tmp = ast;
            while(ast)
            {
                printf ("ast = %d \n", ast->content.token_type);
                ast = ast->left;
            }
             printf("\n");
            ast = tmp;
            ast = ast->left->left->right;
            tmp2 = ast;
            while(ast)
            {
                printf ("ast = %d \n", ast->content.token_type);
                ast = ast->left;
            }
            ast = tmp2->right;
            printf("\n");
            while(ast)
            {
                printf ("ast = %d \n", ast->content.token_type);
                ast = ast->left;
            }
             printf("\n");
            ast = tmp->right;
             while(ast)
            {
                printf ("astt = %d \n", ast->content.token_type);
                ast = ast->left;
            }
            return (0);
        }
    }
}
