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
CFLAGS = -Wall -Wextra -Werror -I$(INC) #-fsanitize=address -g
RM = @rm -rf

#libft
LIBFT_DIR	=	lib/libft/
MLIBX_DIR	=	lib/minilibx/
LIBFT_A		=	lib/libft/libft.a

#Source files
SRC			=	src/main.c \
				src/utils.c \
				src/math/math_1.c \
				src/math/vector.c \
				src/math/sphere.c \
				src/mlx_utils.c \
				src/matrix.c \
				src/inter.c \
				src/inter_cy_utils_1.c \
				src/inter_cy_utils_2.c \
				src/raytrace.c \
				src/hooks.c \
				src/transform.c \
				src/lights.c \
				src/parse/parse.c \
				src/parse/get_scene.c \
				src/parse/free_scene.c \
				src/parse/utils.c \
				src/parse/get_elements/get_camera.c \
				src/parse/get_elements/get_light.c \
				src/parse/get_elements/new_object.c \
				src/parse/get_elements/set_utils.c

#Object files
OBJ			=	$(SRC:%.c=%.o)

INC			= inc/

#OS
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
    O_FLAGS = ./lib/minilibx/libmlx.a -I/include/minilibx/mlx.h -lXext -lX11 -lm -lbsd
else
    O_FLAGS = -lmlx -L/usr/X11/lib -lXext -lX11
endif

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BLACK)Compiling libft...$(COLOUR_END)"
	@make --silent -C $(LIBFT_DIR)
	@echo "$(GREEN)libft successfully compiled.$(COLOUR_END)"
	@make --silent -C $(MLIBX_DIR)
	@echo "$(GREEN)minilibx successfully compiled.$(COLOUR_END)"
	@echo "$(BLACK)Compiling $(NAME)...$(COLOUR_END)"
	@$(CC) $(CFLAGS) -o $(@) -I/usr/local/include $(^) $(O_FLAGS) $(LIBFT_A)
	@echo "$(GREEN)$(NAME) successfully compiled.$(COLOUR_END)"

clean:
	@rm -rf $(OBJ)
	@make clean --silent -C $(LIBFT_DIR)
	@echo "$(YELLOW)All Objects removed.$(COLOUR_END)"

fclean: clean
	@rm -rf $(NAME)
	@make fclean --silent -C $(LIBFT_DIR)
	@echo "$(YELLOW)$(NAME) removed.$(COLOUR_END)"

re: fclean all

debug: re
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(NAME) 2>valgrind.log

debugmac: all
	@echo "$(BLACK)Compiling libft...$(COLOUR_END)"
	@make --silent -C $(LIBFT_DIR)
	@echo "$(GREEN)libft successfully compiled.$(COLOUR_END)"
	@echo "$(BLACK)Compiling $(NAME)...$(COLOUR_END)"
	@$(CC) $(CFLAGS) -o $(@) -I/usr/local/include $(SRC) $(O_FLAGS) $(LIBFT_A)
	@echo "$(GREEN)$(NAME) successfully compiled.$(COLOUR_END)"
	@echo "$(YELLOW)Running $(NAME)...$(COLOUR_END)"
	@./$(NAME)


.PHONY: all clean fclean re bonus