// TODO: move shit that should go to utils lol
#ifndef UTILS_H
# define UTILS_H

# include "../core/structures.h"

// ==== String & File Utilities ====
int		ft_strcmp(const char *s1, const char *s2);
char	*ultimate_trim(t_game *game, char *raw, char *trim_set);
bool	is_fully_space(char *str);
bool	is_number(char *str);
bool	has_valid_cub_extension(const char *filename);

// ==== Math Utilities ====
double	deg_to_rad(double deg);
float	lerp(float start, float end, float t);

// ==== Character Utilities ====
bool	is_space(char c);
bool	is_player(char player);

// ==== Map & Movement Checks ====
bool	check_map(t_game *game);
bool	can_move(t_game *g, double x, double y);
void	attempt_move(t_game *g, t_axis *pos, double dx, double dy);

// ==== Matrix Utilities ====
char	**copy_matrix(t_game *game, char **matrix);

// ==== Error & Memory Management ====
void	ft_free(void **ptr);
void	free_tab(char **state);
void	free_game(t_game *game);
void	destroy_img(t_game *game);
void	display_error_message(const char *msg, bool is_perror);

// ==== Game Timing ====
t_ms	get_timestamp(t_game *game);
bool	should_update(t_game *game);

// ==== Player Actions ====
bool	is_moving(t_game *game);
bool	is_jumping(t_game *game);
void	stand_up(t_player *p, double dt);
void	jump_event(t_player *p, double dt);

#endif
