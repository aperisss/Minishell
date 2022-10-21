NAME := list.a

CC := gcc

CFLAGS := -Wall -Wextra -Werror

SRCDIR := srcs
OBJDIR := objs
INCDIR := ../inc

INC := $(patsubst %.a,$(INCDIR)/%.h,$(NAME))

SRCS := ft_lstadd_back.c   ft_lstclear.c   ft_lstiter.c  ft_lstmap.c  ft_lstsize.c \
ft_lstadd_front.c  ft_lstdelone.c  ft_lstlast.c  ft_lstnew.c  ft_lstdel_first.c

OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

green = /bin/echo -e "\x1b[32m$1\x1b[0m"
red = /bin/echo -e "\x1b[31m$1\x1b[0m"


all: $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)


$(NAME) : $(OBJS)
	$(call green,"Compiling list...")
	ar -rcs $@ $^
	$(call green,"Done")


clean:
	$(call red,"Removing list object files...")
	rm -fd $(OBJS) $(OBJDIR)


fclean:
	$(call red,"Removing list object files and library...")
	rm -fd $(OBJS) $(OBJDIR) $(NAME)


re: fclean all


.PHONY: all clean fclean re


.SILENT: