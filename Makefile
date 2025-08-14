# !!!
# TODO: MAKE SURE THAT THE WILDCARD FOR OBJ FILES IS FINE BY 42NORM

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g

NAME    			=	cub3d
NAME_BONUS			=	cub3d_bonus

SRC_DIR 			=	srcs
BONUS_DIR			=	bonus

CORE_DIR			=	$(SRC_DIR)/core
UTIL_DIR			=	$(SRC_DIR)/utils
INIT_DIR			=	$(CORE_DIR)/init
CHECKER_DIR			=	$(CORE_DIR)/checker
EVENTS_DIR			=	$(CORE_DIR)/events
RAYCAST_DIR			=	$(CORE_DIR)/ray-casting
CLEANUP_DIR			=	$(CORE_DIR)/cleanup
INIT_MLX_DIR		=	$(INIT_DIR)/mlx
INIT_DATA_DIR		=	$(INIT_DIR)/data

OBJ_DIR				=	objs
OBJ_BONUS_DIR		=	bonus_objs

SRCS				=	$(SRC_DIR)/main.c 							\
						$(INIT_DIR)/init_game.c						\
						$(INIT_DIR)/init_player.c					\
						$(INIT_DATA_DIR)/init_data.c				\
						$(INIT_DATA_DIR)/init_map.c					\
						$(INIT_DATA_DIR)/init_rgb.c					\
						$(INIT_DATA_DIR)/init_texture.c				\
						$(INIT_MLX_DIR)/init_mlx.c					\
						$(INIT_MLX_DIR)/load_textures.c				\
						$(EVENTS_DIR)/time.c						\
						$(EVENTS_DIR)/loop.c						\
						$(EVENTS_DIR)/hooks.c						\
						$(EVENTS_DIR)/player.c						\
						$(EVENTS_DIR)/keys.c						\
						$(CLEANUP_DIR)/free_game.c					\
						$(CLEANUP_DIR)/free_mlx.c					\
						$(CHECKER_DIR)/file_checker.c				\
						$(CHECKER_DIR)/map_checker.c				\
						$(RAYCAST_DIR)/casting.c					\
						$(RAYCAST_DIR)/dda.c						\
						$(RAYCAST_DIR)/rotation.c					\
						$(RAYCAST_DIR)/draw_texture.c				\
						$(UTIL_DIR)/error_utils.c					\
						$(UTIL_DIR)/image_utils.c					\
						$(UTIL_DIR)/texture_utils.c					\
						$(UTIL_DIR)/matrix_utils.c					\
						$(UTIL_DIR)/move_utils.c					\
						$(UTIL_DIR)/player_utils.c					\
						$(UTIL_DIR)/string_utils.c

B_CORE_DIR       	= $(BONUS_DIR)/core
B_HUD_DIR			= $(BONUS_DIR)/hud
B_DOOR_DIR			= $(BONUS_DIR)/door
B_UTIL_DIR       	= $(BONUS_DIR)/utils
B_INIT_DIR       	= $(BONUS_DIR)/core/init
B_CHECKER_DIR    	= $(BONUS_DIR)/core/checker
B_EVENTS_DIR     	= $(BONUS_DIR)/core/events
B_RAYCAST_DIR    	= $(BONUS_DIR)/core/ray-casting
B_CLEANUP_DIR    	= $(BONUS_DIR)/core/cleanup
B_INIT_MLX_DIR   	= $(BONUS_DIR)/core/init/mlx
B_INIT_DATA_DIR  	= $(BONUS_DIR)/core/init/data
B_EVENT_INPUT_DIR	= $(BONUS_DIR)/core/events/inputs

BONUS_SRCS			=	$(BONUS_DIR)/main_bonus.c					\
						$(BONUS_DIR)/minimap/minimap_bonus.c		\
						$(BONUS_DIR)/minimap/ray_bonus.c			\
						$(B_INIT_DIR)/init_game_bonus.c				\
						$(B_INIT_DIR)/init_player_bonus.c			\
						$(B_INIT_DIR)/init_weapon_bonus.c			\
						$(B_INIT_DIR)/init_door_bonus.c				\
						$(B_INIT_DATA_DIR)/init_data_bonus.c		\
						$(B_INIT_DATA_DIR)/init_map_bonus.c			\
						$(B_INIT_DATA_DIR)/init_rgb_bonus.c			\
						$(B_INIT_DATA_DIR)/init_texture_bonus.c		\
						$(B_INIT_MLX_DIR)/init_mlx_bonus.c			\
						$(B_INIT_MLX_DIR)/load_textures_bonus.c		\
						$(B_EVENTS_DIR)/time_bonus.c				\
						$(B_EVENTS_DIR)/loop_bonus.c				\
						$(B_EVENTS_DIR)/hooks_bonus.c				\
						$(B_EVENTS_DIR)/player_bonus.c				\
						$(B_EVENT_INPUT_DIR)/keys_bonus.c			\
						$(B_EVENT_INPUT_DIR)/mouse_bonus.c			\
						$(B_CLEANUP_DIR)/free_game_bonus.c			\
						$(B_CLEANUP_DIR)/free_mlx_bonus.c			\
						$(B_CHECKER_DIR)/file_checker_bonus.c		\
						$(B_CHECKER_DIR)/map_checker_bonus.c		\
						$(B_RAYCAST_DIR)/casting_bonus.c			\
						$(B_RAYCAST_DIR)/dda_bonus.c				\
						$(B_RAYCAST_DIR)/rotation_bonus.c			\
						$(B_RAYCAST_DIR)/draw_texture_bonus.c		\
						$(B_HUD_DIR)/hud_bonus.c					\
						$(B_HUD_DIR)/hud_utils_bonus.c				\
						$(B_HUD_DIR)/weapon_bonus.c					\
						$(B_DOOR_DIR)/door_bonus.c					\
						$(B_UTIL_DIR)/error_utils_bonus.c			\
						$(B_UTIL_DIR)/image_utils_bonus.c			\
						$(B_UTIL_DIR)/texture_utils_bonus.c			\
						$(B_UTIL_DIR)/matrix_utils_bonus.c			\
						$(B_UTIL_DIR)/move_utils_bonus.c			\
						$(B_UTIL_DIR)/player_utils_bonus.c			\
						$(B_UTIL_DIR)/string_utils_bonus.c

OBJS				= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS			= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

MLX_DIR 			=	libs/mlx
LIBFT_DIR			=	libs/libft
GNL_DIR				=	libs/gnl

MLX					=	$(MLX_DIR)/libmlx_Linux.a
LIBFT				=	$(LIBFT_DIR)/libft.a
GNL					=	$(GNL_DIR)/libgnl.a
LIBS				=	$(MLX) $(GNL) $(LIBFT) -lXext -lX11 -lm

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(LIBFT) $(MLX)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes/core -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(NAME_BONUS): $(BONUS_OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(NAME_BONUS)

$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c $(LIBFT) $(MLX)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes/core -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

$(LIBS): $(LIBFT) $(MLX) $(GNL)

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
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(GNL_DIR) fclean


re: fclean all

# Usage: make valgrind MAP=path/to/map.cub FLAGS=-b # ! DELETE COMMENT, REMOVE ANYWAY LOL # TODO: REMOVE
valgrind:
	@if echo "$(FLAGS)" | grep -q "\-b"; then \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d_bonus $(MAP); \
	else \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d $(MAP); \
	fi

mlx: $(MLX)

# TODO: REMOVE
rem_comments:
	@echo "Stripping comments with Python..."
	@/usr/bin/env python3 rem_comments.py

.PHONY: all clean fclean re valgrind mlx rem_comments
