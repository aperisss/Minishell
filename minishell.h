#ifndef MINISHELL_H
#define MINISHELL_H


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
    WORDS,
    ONE_REDIR_LEFT,
    ONE_REDIR_RIGHT,
    DOUBLE_REDIR_LEFT,
    DOUBLE_REDIR_RIGHT,
    CMD_NAME,
    CMD_SUFFIX,
    CMD_PREFIX,
    IO_REDIRECT,
    IO_FILE,
    IO_HERE,
    SIMPLE_COMMAND,
    OPERATEUR_SEQUENCE,
    PIPE_SEQUENCE,
    PIPE,
    CLOSE_PAR,
    OPEN_PAR,
    AND,
    OR,
    WILDCARDS,
    END,
} t_token_type;

typedef struct s_token
{
    struct s_token *next;
    t_token_type token;
} t_token;

typedef struct s_stack
{
    struct s_stack *next;
    t_token_type *type_stack;
} t_stack;

int     ft_strchr2( char d, char c);
int     ft_lenword(char const *str, char c);
char	*ft_strdup2(char const *src, char c);
int     ft_countword(char const *str, char c);
char	**ft_split(char const *s, char c);
t_token *lexer(char *input);
int     ft_strcmp(char *s1, char *s2);

#endif
#endif 