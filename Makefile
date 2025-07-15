# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

# Project name
NAME    	=	cub3d

# Directories
SRC_DIR 	=	srcs

# Subdirectories
INIT_DIR	=	$(SRC_DIR)/init
CHECKER_DIR	=	$(SRC_DIR)/checker
MLX_SRC_DIR	=	$(SRC_DIR)/mlx
LOOP_DIR	=	$(SRC_DIR)/gameloop
UTIL_DIR	=	$(SRC_DIR)/utils
CLEANUP_DIR	=	$(SRC_DIR)/cleanup
GNL_DIR		=	$(SRC_DIR)/gnl

# Object directory
OBJ_DIR		=	objs

# Libraries directories
LIBFT_DIR	=	libs/libft
MLX_DIR 	=	libs/mlx

# Source files
SRCS    =	$(SRC_DIR)/main.c 					\
			$(INIT_DIR)/init_game.c				\
			$(INIT_DIR)/init_data.c				\
			$(INIT_DIR)/init_rgb.c				\
			$(INIT_DIR)/init_texture.c			\
			$(INIT_DIR)/init_map.c				\
			$(INIT_DIR)/init_player.c			\
			$(INIT_DIR)/init_window.c			\
			$(LOOP_DIR)/loop.c					\
			$(LOOP_DIR)/input.c					\
			$(LOOP_DIR)/hooks.c					\
			$(CLEANUP_DIR)/free.c				\
			$(CHECKER_DIR)/file_checker.c		\
			$(CHECKER_DIR)/map_checker.c		\
			$(UTIL_DIR)/display_message.c		\
			$(UTIL_DIR)/str_utils.c				\
			$(UTIL_DIR)/matrix_utils.c			\
			$(UTIL_DIR)/debug.c					\
			$(UTIL_DIR)/error_handling.c		\
			$(GNL_DIR)/get_next_line.c			\
			$(GNL_DIR)/get_next_line_utils.c	\

# ! debug.c is for debugging purposes and shall be removed later

# Object files
OBJS    =	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBS    =	$(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a -lXext -lX11 -lm

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

# ? USAGE: make valgrind MAP=path/to/map.cub
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d $(MAP)

.PHONY: all clean fclean re valgrind
