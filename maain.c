#include "minishell.h"

int main(int ac, char **av, char **envp)
{
    char *input;
    t_btree *ast;
    t_btree *tmp;
    t_btree *tmp2;
    t_btree *tmp3;
    input = NULL;
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
            ast = btree_create(&token_list);
            tmp3 = ast;
            printf(" ast = %d\n", ast->content.token_type);
            ast = ast->left;
            printf(" ast = %d\n", ast->content.token_type);
            ast = ast->left;
            tmp = ast;

	        while(ast)
	        {
		        printf("ast = %d\n", ast->content.token_type);
                if (ast->content.token_type == SIMPLE_COMMAND)
                {
                    tmp2 = ast;
                    ast = ast->right;
                    while(ast)
                    {
                        printf("cmd droite = %d\n", ast->content.token_type);
                        ast = ast->right;
                    }
                    ast = tmp2;
                }
		        ast = ast->left;
	        }
            ast = tmp;
	        printf("\n");
            ast = ast->right;
            tmp2= ast;
            while(ast)
            {
                printf("cmd droite = %d\n", ast->content.token_type);
                ast = ast->right;
            }
            ast = tmp2;
            ast = ast->left;
            while(ast)
            {
                printf("cmd gauche = %d\n", ast->content.token_type);
                ast = ast->left;
            }
            ast = tmp3;
            ast = ast->right;
            tmp3 = ast;
            printf("\n");
            while(ast)
            {
                printf("cmd final droite = %d\n", ast->content.token_type);
                ast = ast->right;
            }
            ast = tmp3;
            while(ast)
            {
                printf("cmd final gauche = %d\n", ast->content.token_type);
                ast = ast->left;
            }
            return (0);
        }
    }
}
