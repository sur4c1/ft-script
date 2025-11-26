# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 13:24:40 by bguyot            #+#    #+#              #
#    Updated: 2025/08/26 16:50:22 by yyyyyy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	libft.a

SRCDIR			=	srcs/
OBJDIR			=	objs/
INCDIR			=	incs/

DIR_ARR			=	arr/
FILES_ARR		=	sort_int_tab	tabmax	tabmed	tabmin
FT_ARR			=	$(addprefix $(DIR_ARR)ft_, $(FILES_ARR))

DIR_CAST		=	cast/
FILES_CAST		=	tolower	toupper	atoi	itoa	utoa	utoa_base			\
					ultoa_base	atobuf atou atol atos atous atoul
FT_CAST			=	$(addprefix $(DIR_CAST)ft_, $(FILES_CAST))

DIR_CHECK		=	check/
FILES_CHECK		=	isalnum	isalpha	isascii	isdigit	isprint	isspace
FT_CHECK		=	$(addprefix $(DIR_CHECK)ft_, $(FILES_CHECK))

DIR_LIST		=	list/
FILES_LIST			=	lstadd_back	lstadd_front	lstclear	lstdelone		\
					lstiter	lstlast	lstmap	lstmax	lstmin	lstnew	lstnnext	\
					lstsize
FT_LIST			=	$(addprefix $(DIR_LIST)ft_, $(FILES_LIST))

DIR_MATH		=	math/
FILES_MATH		=	abs	max	min	sqrt	sign
FT_MATH			=	$(addprefix $(DIR_MATH)ft_, $(FILES_MATH))

DIR_MEMORY		=	memory/
FILES_MEMORY	=	bzero	calloc	memcat	memchr	memcmp	memcpy	memmove		\
					memset	memdup
FT_MEMORY		=	$(addprefix $(DIR_MEMORY)ft_, $(FILES_MEMORY))

DIR_PUT			=	put/
FILES_PUT		=	putchar_fd	putendl_fd	putnbr_fd	putstr_fd	puttab_fd
FT_PUT			=	$(addprefix $(DIR_PUT)ft_, $(FILES_PUT))

DIR_STRING		=	string/
FILES_STRING	=	split	strchr	strcmp	strcontain	strdup	striteri		\
					strjoin	strlcat	strlcpy	strlen	strmapi	strncmp	strndup		\
					strnstr	strrchr	strnchr	strtrim	substr	tabjoin	strgen
FT_STRING		=	$(addprefix $(DIR_STRING)ft_, $(FILES_STRING))

DIR_BUFF		=	buff/
FILES_BUFF		=	bufcat	bufclear bufdup
FT_BUFF			=	$(addprefix $(DIR_BUFF)ft_, $(FILES_BUFF))

DIR_GNL			=	gnl/
FILES_GNL		=	gnl
FT_GNL			=	$(addprefix $(DIR_GNL)ft_, $(FILES_GNL))

DIR_PRITNF		=	printf/
FILES_PRINTF	=	ft_printf	__ft_printf
FT_PRINTF		=	$(addprefix $(DIR_PRITNF), $(FILES_PRINTF))

DIR_GETOPT		=	getopt/
FILES_GETOPT	=	getopt	getopt_long	getopt_long_only
FT_GETOPT		=	$(addprefix $(DIR_GETOPT)ft_, $(FILES_GETOPT))

DIR_GLOBALS		=	globals/
FILES_GLOBALS	=	globals
FT_GLOBALS		=	$(addprefix $(DIR_GLOBALS)ft_, $(FILES_GLOBALS))

SRCS 			=	$(FT_ARR)	$(FT_CAST)	$(FT_CHECK)	$(FT_LIST)	$(FT_MATH)	\
					$(FT_MEMORY) $(FT_PUT)	$(FT_STRING)	$(FT_GNL)			\
					$(FT_BUFF)	$(FT_PRINTF)	$(FT_GETOPT)	$(FT_GLOBALS)

OBJS 			=	$(addprefix $(OBJDIR), $(addsuffix .o, $(SRCS)))

CC				=	@gcc
RM				=	@rm -rf
SH				=	@bash
CFLAGS			=	-Wall -Wextra -Werror -I $(INCDIR) -g3 $(DEFINES)

OBJ_COLOR		=	"\e[38;5;147m"
CLN_COLOR		=	"\e[38;5;124m"
BIN_COLOR		=	"\e[38;5;129m"
ERRASE_LINE		=	"\e[2K\r"

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf $(ERRASE_LINE)$(BIN_COLOR)"\t"$(NAME)"\t\t\t\t[ ✓ ]\n\e[0m"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf $(ERRASE_LINE)$(OBJ_COLOR)"\t"$@"\e[0m"

clean:
	$(RM) $(OBJDIR)
	@printf $(CLN_COLOR)"\tclean "$(NAME)" objects\t\t[ ✓ ]\n\e[0m"

fclean: clean
	$(RM) $(NAME)
	@printf $(CLN_COLOR)"\tclean "$(NAME)" binary\t\t[ ✓ ]\n\e[0m"

re: fclean all

test: all
	@$(SH) ./test/test.sh

echo:
	@echo $(OBJS)

.PHONY:	all clean fclean re echo
