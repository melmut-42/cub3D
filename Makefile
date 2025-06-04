# Compiler and flags
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# Project name
NAME    = cub3d

# Directories
SRC_DIR = srcs
CHECKER_DIR = $(SRC_DIR)/checker

# Object directory
OBJ_DIR = objs

# Libraries directories
LIBFT_DIR = libs/libft
MLX_DIR  = libs/mlx

# Source files
SRCS    =	$(SRC_DIR)/main.c 				\
			$(CHECKER_DIR)/file_checker.c

# Object files
OBJS    = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBS    = $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a -lXext -lX11 -lm

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# How to compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

# Clean up
clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

# Bonus targets
.PHONY: all clean fclean re
