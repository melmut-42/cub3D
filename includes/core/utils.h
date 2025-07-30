#ifndef UTILS_H
# define UTILS_H

# include "../core/structures.h"

// =============================== String ===============================
int		ft_strcmp(const char *s1, const char *s2);
char	*ultimate_trim(t_game *game, char *raw, char *trim_set);

// =============================== Checks ===============================
bool	is_space(char c);
bool	is_player(char player);
bool	is_fully_space(char *str);
bool	is_number(char *str);
bool	has_valid_cub_extension(const char *filename);
bool	check_map(t_game *game);

// ============================== Movement ==============================
bool	can_move(t_map *map, double x, double y);
void	attempt_move(t_map *map, t_axis *pos, double dx, double dy);

// =============================== Matrix ===============================
char	**copy_matrix(t_game *game, char **matrix);

// =============================== Errors ===============================
void	display_error_message(const char *msg, bool is_perror);

// =============================== Memory ===============================
void	free_tab(char **state);
void	free_game(t_game *game);
void	ft_free(void **ptr);
void	destroy_img(t_game *game);

// ================================ MLX ================================
bool	init_mlx(t_game *game, int width, int height, char *title);
bool	init_frame_image(t_game *game);
bool	load_game_textures(t_game *game);

// =============================== Time ===============================
t_ms	get_timestamp(t_game *game);
bool	should_update(t_game *game);

#endif
