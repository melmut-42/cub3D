#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# include "../core/macros.h"
# include "../core/structures.h"

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# include "../core/utils.h"
# include "../engine/init.h"
# include "../engine/door.h"
# include "../engine/hooks.h"
# include "../engine/render.h"
# include "../engine/textures.h"
# include "../errors/error_logs.h"

// ==== Game Initialization & Loop ====
t_game	*init_game(char *map_path);
int		gameloop(t_game *game);

// ==== Game Exit ====
int		handle_close(t_game *game);
void	free_game(t_game *game);

#endif
