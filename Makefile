NAME := minishell

CC := gcc
FLAGS := -Wall -Wextra -Werror -g
LINK := -lreadline

SRCDIR := srcs
OBJDIR := objs

SRCS_ := btree.c                builtin2.c     exec_builtin.c   expand_quote.c  main.c            wildcards_readdir.c \
         btree_cmd_construct.c  builtin3.c     exec_cmd.c       fill_hd.c       wildcards_utils.c get_input.c \
         btree_pipe.c           builtin.c      exec_pipe_seq.c  free_fct.c      tokener.c \
         btree_utils2.c         check_quote.c  exec_tree.c      free_struct.c   tokener_utils.c \
         btree_utils.c          env.c          exec_utils.c     here_doc.c      utils.c \
         btree_wildcards.c      env_utils.c    expand_env.c     lexer.c         wildcards.c cd.c cd_utils.c export_utils.c

SRCS := $(patsubst %,$(SRCDIR)/%,$(SRCS_))


OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS_))

INC := minishell.h

LIBFT := lib/libft/libft.a

LIBLST := lib/list/list.a

LIBS := $(LIBFT) $(LIBLST)

green = /bin/echo -e "\x1b[32m$1\x1b[0m"
red = /bin/echo -e "\x1b[31m$1\x1b[0m"


all : $(NAME)


$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@


$(NAME) : $(OBJ) $(LIBS) Makefile
	$(call green,"Compiling...")
	$(CC) -g  $(OBJ) -o $(NAME) $(LIBS) $(LINK)
	$(call green,"Done.")


clean:
	$(call red,"Cleaning...")
	rm -fd $(OBJ) $(OBJDIR)
	make -C $(dir $(LIBFT)) clean
	make -C $(dir $(LIBLST)) clean
	$(call red,"Done.")


fclean:
	$(call red,"Cleaning everything...")
	rm -fd $(OBJ) $(NAME) $(OBJDIR)
	make -C $(dir $(LIBFT)) fclean
	make -C $(dir $(LIBLST)) fclean
	$(call red,"Done.")


%.a: 
	make -C $(dir $@)


re:
	make fclean
	make all


.PHONY: clean fclean re all

.SILENT :
