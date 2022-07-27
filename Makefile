NAME := minishell

CC := gcc
FLAGS := -Wall -Wextra -Werror
LINK := -lreadline

SRCDIR := srcs
OBJDIR := objs

SRCS_ := check_quote.c  lexer.c  main.c
SRCS := $(patsubst %,$(SRCDIR)/%,$(SRCS_))


OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_))

INC := minishell.h

LIBFT := libft/libft.a



all : $(NAME)


$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@


$(NAME) : $(OBJ) $(LIBFT)
	$(CC)  $(OBJ) -o $(NAME) $(LIBFT) $(LINK)


clean:
	rm -fd $(OBJ) $(OBJDIR)
	make -C $(dir $(LIBFT)) clean


fclean:
	rm -fd $(OBJ) $(NAME) $(OBJDIR)
	make -C $(dir $(LIBFT)) fclean


$(LIBFT):
	make -C $(dir $(LIBFT))


re:
	make fclean
	make all


.PHONY: clean fclean re all
