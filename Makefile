#Colors
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
COLOUR_END	=	\033[0m

#Targets
NAME = miniRT

#Compiler flags
CC = @cc
CFLAGS = -Wall -Wextra -Werror -I$(INC) -g #-fsanitize=address,undefined
RM = @rm -rf

#libft
LIBFT_DIR	=	lib/libft/
LIBFT_A		=	lib/libft/libft.a

#Source files
SRC			=	src/main.c

#Object files
OBJ			=	$(SRC:%.c=%.o)

INC			= inc/

#OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    O_FLAGS = linux
else
    O_FLAGS = -lmlx -L/usr/X11/lib -lXext -lX11
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLACK)Compiling libft...$(COLOUR_END)"
	@make --silent -C $(LIBFT_DIR)
	@echo "$(GREEN)libft successfully compiled.$(COLOUR_END)"
	@echo "$(BLACK)Compiling $(NAME)...$(COLOUR_END)"
	@$(CC) $(CFLAGS) -o $(@) -I/usr/local/include $(^) $(O_FLAGS) $(LIBFT_A)
	@echo "$(GREEN)$(NAME) successfully compiled.$(COLOUR_END)"

clean:
	@make clean --silent -C $(LIBFT_DIR)
	@echo "$(YELLOW)All Objects removed.$(COLOUR_END)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean --silent -C $(LIBFT_DIR)
	@echo "$(YELLOW)$(NAME) removed.$(COLOUR_END)"

re: fclean all

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --track-fds=yes --track-origins=yes ./minishell 2>valgrind.log

.PHONY: all clean fclean re bonus