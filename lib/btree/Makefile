NAME := btree.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror

SRCDIR := srcs
OBJDIR := objs
INCDIR := ../inc

INC := $(patsubst %.a,$(INCDIR)/%.h,$(NAME))

SRCS := btree_apply_infix.c  btree_apply_prefix.c  btree_apply_suffix.c  btree_create_node.c

OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))


all: $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)


$(NAME) : $(OBJS)
	ar -rcs $@ $^


clean:
	rm -fd $(OBJS) $(OBJDIR)


fclean:
	rm -fd $(OBJS) $(OBJDIR) $(NAME)


re: fclean all


.PHONY: all clean fclean re