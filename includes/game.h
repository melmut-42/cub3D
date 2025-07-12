#ifndef GAME_H
# define GAME_H

// ============= Includes =============

# include "stdbool.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "fcntl.h"

# include "../libs/libft/libft.h"
# include "../libs/mlx/mlx.h"

# include "structures.h"
# include "error_logs.h"

// ========================== Initialization Functions ==========================

t_game	*init_game(char *map_path);
bool	init_data(t_game *game);
bool	process_texture_data(t_game *game, t_texture *texture, int fd);
void	process_rgb(t_game *game, int rgb[3], char *data);

// ============================ Checker Functions ============================

bool	has_valid_cub_extension(const char *filename);

// ================================= Utils =================================

int		ft_strcmp(const char *s1, const char *s2);
void	display_error_message(const char *msg, bool is_perror);
char	*get_next_line(int fd);
bool	is_space(char c);
bool	does_fully_include_spaces(char *str);
bool	is_number(char *str);
void	free_tab(char **state);

// ================================ GNL Utils ================================

int		ft_is_newline_char(const char *s);
char	*ft_update_repo(char *total_line, char *repo);

#endif