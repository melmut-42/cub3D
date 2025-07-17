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
EVENTS_DIR	=	$(SRC_DIR)/events
RAYCAST_DIR	=	$(SRC_DIR)/ray-casting
UTIL_DIR	=	$(SRC_DIR)/utils
CLEANUP_DIR	=	$(SRC_DIR)/cleanup
GNL_DIR		=	$(SRC_DIR)/gnl

# Object directory
OBJ_DIR		=	objs

# Source files
SRCS    	=	$(SRC_DIR)/main.c 					\
				$(INIT_DIR)/init_game.c				\
				$(INIT_DIR)/init_data.c				\
				$(INIT_DIR)/init_rgb.c				\
				$(INIT_DIR)/init_texture.c			\
				$(INIT_DIR)/init_map.c				\
				$(INIT_DIR)/init_player.c			\
				$(INIT_DIR)/init_window.c			\
				$(EVENTS_DIR)/loop.c				\
				$(EVENTS_DIR)/input.c				\
				$(EVENTS_DIR)/hooks.c				\
				$(EVENTS_DIR)/time.c				\
				$(CLEANUP_DIR)/free.c				\
				$(CHECKER_DIR)/file_checker.c		\
				$(CHECKER_DIR)/map_checker.c		\
				$(RAYCAST_DIR)/casting.c			\
				$(UTIL_DIR)/display_message.c		\
				$(UTIL_DIR)/str_utils.c				\
				$(UTIL_DIR)/matrix_utils.c			\
				$(UTIL_DIR)/debug.c					\
				$(UTIL_DIR)/error_handling.c		\
				$(GNL_DIR)/get_next_line.c			\
				$(GNL_DIR)/get_next_line_utils.c	\

# ! debug.c is for debugging purposes and shall be removed later

# Object files
OBJS    	=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries directories
LIBFT_DIR	=	libs/libft
MLX_DIR 	=	libs/mlx

# Libraries
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX			=	$(MLX_DIR)/libmlx_Linux.a
LIBS		=	$(MLX) $(LIBFT) -lXext -lX11 -lm

# Build rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT) $(MLX)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

mlx: $(MLX)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Usage: make valgrind MAP=path/to/map.cub
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d $(MAP)

.PHONY: all clean fclean re valgrind mlx
