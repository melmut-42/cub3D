# !!!
# TODO: MAKE SURE THAT THE WILDCARD FOR OBJ FILES IS FINE BY 42NORM

# Compiler and flags
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g

# Project name
NAME    		=	cub3d

# Directories
SRC_DIR 		=	srcs

# Subdirectories
CORE_DIR		=	$(SRC_DIR)/core
UTIL_DIR		=	$(SRC_DIR)/utils
INIT_DIR		=	$(CORE_DIR)/init
CHECKER_DIR		=	$(CORE_DIR)/checker
EVENTS_DIR		=	$(CORE_DIR)/events
RAYCAST_DIR		=	$(CORE_DIR)/ray-casting
CLEANUP_DIR		=	$(CORE_DIR)/cleanup

INIT_MLX_DIR	=	$(INIT_DIR)/mlx
INIT_DATA_DIR	=	$(INIT_DIR)/data

EVENT_INPUT_DIR	=	$(EVENTS_DIR)/inputs

# Object directory
OBJ_DIR			=	objs

# Source files
SRCS			=	$(SRC_DIR)/main.c 					\
					$(INIT_DIR)/init_game.c				\
					$(INIT_DIR)/init_player.c			\
					$(INIT_DATA_DIR)/init_data.c		\
					$(INIT_DATA_DIR)/init_map.c			\
					$(INIT_DATA_DIR)/init_rgb.c			\
					$(INIT_DATA_DIR)/init_texture.c		\
					$(INIT_MLX_DIR)/init_mlx.c			\
					$(INIT_MLX_DIR)/load_textures.c		\
					$(EVENTS_DIR)/time.c				\
					$(EVENTS_DIR)/loop.c				\
					$(EVENTS_DIR)/hooks.c				\
					$(EVENTS_DIR)/player.c				\
					$(EVENT_INPUT_DIR)/keys.c			\
					$(EVENT_INPUT_DIR)/mouse.c			\
					$(CLEANUP_DIR)/free_game.c			\
					$(CLEANUP_DIR)/free_mlx.c			\
					$(CHECKER_DIR)/file_checker.c		\
					$(CHECKER_DIR)/map_checker.c		\
					$(RAYCAST_DIR)/casting.c			\
					$(RAYCAST_DIR)/rotation.c			\
					$(RAYCAST_DIR)/draw_texture.c		\
					$(UTIL_DIR)/debug.c					\
					$(UTIL_DIR)/error_utils.c			\
					$(UTIL_DIR)/image_utils.c			\
					$(UTIL_DIR)/matrix_utils.c			\
					$(UTIL_DIR)/move_utils.c			\
					$(UTIL_DIR)/string_utils.c

# ! debug.c is for debugging purposes and shall be removed later

# Object files
OBJS    		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries directories
MLX_DIR 		=	libs/mlx
LIBFT_DIR		=	libs/libft
GNL_DIR			=	libs/gnl

# Libraries
MLX				=	$(MLX_DIR)/libmlx_Linux.a
LIBFT			=	$(LIBFT_DIR)/libft.a
GNL				=	$(GNL_DIR)/libgnl.a
LIBS			=	$(MLX) $(GNL) $(LIBFT) -lXext -lX11 -lm

# Build rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT) $(MLX)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes/core -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	@$(MAKE) -C $(GNL_DIR)

$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean


re: fclean all

# Usage: make valgrind MAP=path/to/map.cub
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d $(MAP)

mlx: $(MLX)

rem_comments:
	@echo "Stripping comments with Python..."
	@/usr/bin/env python3 rem_comments.py

.PHONY: all clean fclean re valgrind mlx rem_comments
