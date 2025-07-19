#ifndef GAME_H
# define GAME_H

// ============= Includes =============

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"

# include "structures.h"
# include "error_logs.h"
# include "textures.h"

// ========================= Initialization Functions =========================

t_game	*init_game(char *map_path);
bool	init_data(t_game *game);
bool	init_player(t_game *game);
bool	process_texture_data(t_game *game, t_texture *texture, int fd);
void	process_rgb(t_game *game, int rgb[RGB_CONSTANT], char *data);
bool	process_map_data(t_game *game, t_map *map, int fd);
bool	does_texture_attr_completed(t_texture *texture);

// ========================= MLX Functions =========================

bool	init_mlx(t_game *game, int width, int height, char *title);
bool	init_frame_image(t_game *game);
bool	load_game_textures(t_game *game);

// ======================= Game Loop Functions =======================
int		gameloop(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_mouse(int x, int y, t_game *game);
void	init_hooks(t_game *game);
void 	update_player_movement(t_game *g, t_player *p, t_map *map);
void 	update_player_vertical(t_player *p, double dt);

// =========================== Render Functions ===========================

void	cast_ray(t_game *game, t_ray *ray, int x);
void	draw_texture(t_game *g, t_ray *ray, int x);
void	draw_column(t_game *g, t_ray *ray, int x);
void	rotate_vector(t_data *data, t_axis *vec, double angle);

// ============================ Free Functions ============================

void	free_game(t_game *game);
void	free_tab(char **state);
void	ft_free(void **ptr);

// =========================== Checker Functions ===========================

bool	has_valid_cub_extension(const char *filename);
bool	check_map(t_game *game);


// ============================= Time Functions =============================

t_ms	get_curr_time(t_game *game);
bool	should_update(t_game *game);


// ================================ Utils ================================

int		ft_strcmp(const char *s1, const char *s2);
void	display_error_message(const char *msg, bool is_perror);
char	*get_next_line(int fd);
bool	is_space(char c);
bool	is_player(char player);
bool	does_fully_include_spaces(char *str);
bool	is_number(char *str);
char	*ultimate_trim(t_game *game, char *raw, char *trim_set);
char	**copy_matrix(t_game *game, char **matrix);
bool	can_move(t_map *map, double x, double y);
void	attempt_move(t_map *map, t_axis *pos, double dx, double dy);

// =============================== GNL Utils ===============================

int		ft_is_newline_char(const char *s);
char	*ft_update_repo(char *total_line, char *repo);
void	clear_get_next_line(int fd);

// =============================== Debug Utils ===============================

void display_game(const t_game *g);

#endif
