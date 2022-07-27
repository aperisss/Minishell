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
    RET_TO,
    RET_FROM,
    DLESS,
    DGREAT,
    CMD_NAME,
    CMD_WORD,
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
    FILENAME,
    END,
}   t_token_type;

typedef struct s_token
{
    struct s_token *next;
    t_token_type token;
} t_token;

typedef struct s_stack
{
    struct s_stack *next;
    t_token_type token;
} t_stack;

int     ft_strchr2( char d, char c);
int     ft_lenword(char const *str, char c);
char	*ft_strdup2(char const *src, char c);
int     ft_countword(char const *str, char c);
char	**ft_split(char const *s, char c);
t_token *lexer(char *input);
int     ft_strcmp(char *s1, char *s2);

t_stack  *ft_stacklast(t_stack *stack);
void    ft_lstadd_back(t_stack **stack, int token);
void    reduce(t_stack **stack_list, t_token **token_list, int token, int nb_reduce);
void    shift(t_stack **stack_list, t_token **token_list);
int     parsing(t_token *token_list);
int     state0(t_stack **stack, t_token **token_list);
void    state1(t_stack **stack, t_token **token_list);
void    state2(t_stack **stack, t_token **token_list);
void    state3(t_stack **stack, t_token **token_list);
void    state3bis(t_stack **stack, t_token **token_list);
void    state6(t_stack **stack, t_token **token_list);
void    state6bis(t_stack **stack, t_token **token_list);
void    state7(t_stack **stack, t_token **token_list);
void    state7bis(t_stack **stack, t_token **token_list);
void    state8(t_stack **stack, t_token **token_list);
void    state9(t_stack **stack, t_token **token_list);
void    state10(t_stack **stack, t_token **token_list);
void    state11(t_stack **stack, t_token **token_list);
void    state12(t_stack **stack, t_token **token_list);
void    state14(t_stack **stack, t_token **token_list);
void    state15(t_stack **stack, t_token **token_list);
void    state16(t_stack **stack, t_token **token_list);
void    state16bis(t_stack **stack, t_token **token_list);
void    state17(t_stack **stack, t_token **token_list);
void    state17bis(t_stack **stack, t_token **token_list);
void    state18(t_stack **stack, t_token **token_list);
void    state19(t_stack **stack, t_token **token_list);
void    state20(t_stack **stack, t_token **token_list);
void    state21(t_stack **stack, t_token **token_list);
void    state22(t_stack **stack, t_token **token_list);
void    state23(t_stack **stack, t_token **token_list);
void    state26(t_stack **stack, t_token **token_list);
void    state29(t_stack **stack, t_token **token_list);
void    state29bis(t_stack **stack, t_token **token_list);
void    state31(t_stack **stack, t_token **token_list);
void    state32(t_stack **stack, t_token **token_list);
void    state32bis(t_stack **stack, t_token **token_list);
void    state33(t_stack **stack, t_token **token_list);
void    state34(t_stack **stack, t_token **token_list);
void    state35(t_stack **stack, t_token **token_list);
void    state35bis(t_stack **stack, t_token **token_list);
void    state36(t_stack **stack, t_token **token_list);
void    state37(t_stack **stack, t_token **token_list);
void    state38(t_stack **stack, t_token **token_list);
void    state39(t_stack **stack, t_token **token_list);
void    state40(t_stack **stack, t_token **token_list);
void    state40bis(t_stack **stack, t_token **token_list);


#endif
#endif 