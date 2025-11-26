include source.mk
NAME    =   ft_script

SDIR	=	srcs/
HDIR	=	incs/
LDIR	=	libs/
ODIR	=	objs/

LIBS	=	libft/libft.a
OBJS	=	$(addsuffix .o, $(addprefix $(ODIR), $(SRCS)))

CFLAGS	=	-Wall -Werror -Wextra -I$(HDIR) -I$(LDIR)$(dir $(LIBS))
# CFLAGS +=	-g -fsanitize=address

LFLAGS	=	$(addprefix -L$(LDIR), $(dir $(LIBS))) -lft
# LFLAGS +=	-fsanitize=address

RM		=	@rm -rf
CC		=	@cc
MKDIR	=	@mkdir -p

all: $(NAME)

$(NAME):	$(OBJS) $(addprefix $(LDIR), $(LIBS))
	$(CC) $(OBJS) $(LFLAGS) -o $@

$(ODIR)%.o:	$(SDIR)%.c
	$(MKDIR) $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(LDIR)%.a:
	$(MAKE) -C $(dir $@)

fclean:	clean
	$(RM) $(NAME)

clean:
	$(RM) $(ODIR)
	$(MAKE) -C $(dir $(addprefix $(LDIR), $(LIBS))) fclean

re: fclean all

.PHONY: all fclean clean re
