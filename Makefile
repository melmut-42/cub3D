# Compiler and flags
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

# Project name
NAME			=	cub3D

# Directories
SRCS_DIR		=	srcs
CORE_DIR		=	$(SRCS_DIR)/core
HUD_DIR			=	$(SRCS_DIR)/hud
DOOR_DIR		=	$(SRCS_DIR)/door
UTILS_DIR		=	$(SRCS_DIR)/utils
MINIMAP_DIR		=	$(SRCS_DIR)/minimap

# Subdirectories (Core)
INIT_DIR		=	$(CORE_DIR)/init
EVENTS_DIR		=	$(CORE_DIR)/events
INPUTS_DIR		=	$(CORE_DIR)/events/inputs
RAYCAST_DIR		=	$(CORE_DIR)/ray-casting
CHECKER_DIR		=	$(CORE_DIR)/checker
CLEANUP_DIR		=	$(CORE_DIR)/cleanup
INIT_MLX_DIR	=	$(CORE_DIR)/init/mlx
INIT_DATA_DIR	=	$(CORE_DIR)/init/data

# Source files
SRCS			=	$(SRCS_DIR)/main.c				\
					$(HUD_DIR)/hud.c				\
					$(HUD_DIR)/weapon.c				\
					$(HUD_DIR)/hud_utils.c			\
					$(HUD_DIR)/init_weapon.c		\
					$(DOOR_DIR)/ray_doors.c			\
					$(DOOR_DIR)/init_doors.c		\
					$(DOOR_DIR)/interactions.c		\
					$(DOOR_DIR)/door_movement.c		\
					$(DOOR_DIR)/draw_doors.c		\
					$(INIT_DIR)/init_game.c			\
					$(INIT_DIR)/init_player.c		\
					$(UTILS_DIR)/move_utils.c		\
					$(UTILS_DIR)/error_utils.c		\
					$(UTILS_DIR)/image_utils.c		\
					$(UTILS_DIR)/string_utils.c		\
					$(UTILS_DIR)/player_utils.c		\
					$(UTILS_DIR)/matrix_utils.c		\
					$(UTILS_DIR)/texture_utils.c	\
					$(INPUTS_DIR)/keys.c			\
					$(INPUTS_DIR)/mouse.c			\
					$(EVENTS_DIR)/time.c			\
					$(EVENTS_DIR)/loop.c			\
					$(EVENTS_DIR)/hooks.c			\
					$(EVENTS_DIR)/player.c			\
					$(CLEANUP_DIR)/free_mlx.c		\
					$(CLEANUP_DIR)/free_game.c		\
					$(CHECKER_DIR)/map_checker.c	\
					$(CHECKER_DIR)/file_checker.c	\
					$(MINIMAP_DIR)/minimap.c		\
					$(MINIMAP_DIR)/ray.c			\
					$(RAYCAST_DIR)/casting.c		\
					$(RAYCAST_DIR)/rotation.c		\
					$(RAYCAST_DIR)/draw_texture.c	\
					$(INIT_MLX_DIR)/init_mlx.c		\
					$(INIT_MLX_DIR)/load_textures.c	\
					$(INIT_DATA_DIR)/init_map.c		\
					$(INIT_DATA_DIR)/init_rgb.c		\
					$(INIT_DATA_DIR)/init_data.c	\
					$(INIT_DATA_DIR)/init_texture.c

# Object files
OBJ_DIR			=	objs
OBJS			=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

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

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(LIBFT) $(MLX)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes/core -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBS): $(LIBFT) $(MLX) $(GNL)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	@$(MAKE) -C $(GNL_DIR)

$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then											\
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR);	\
	fi
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(GNL_DIR)" ]; then $(MAKE) -C $(GNL_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) fclean; fi
	@if [ -d "$(GNL_DIR)" ]; then $(MAKE) -C $(GNL_DIR) fclean; fi

re: fclean all

mlx: $(MLX)

mlx_del:
	@if [ -d "$(MLX_DIR)" ]; then	\
	@rm -rf $(MLX_DIR);				\
	@echo "MLX removed!"; fi

# Usage: make valgrind MAP=path/to/map.cub
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d $(MAP);

.PHONY: all clean fclean re mlx mlx_del valgrind
