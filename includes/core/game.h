#ifndef GAME_H
# define GAME_H

// ============================ Standard Libraries ============================
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

// ============================= Project Structures ===========================
# include "../core/structures.h"

// ========================= External Libraries (TODO) ========================
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

// ============================== Project Modules =============================
# include "../errors/debug.h"
# include "../errors/error_logs.h"
# include "../engine/textures.h"
# include "../engine/init.h"
# include "../engine/hooks.h"
# include "../engine/render.h"
# include "../engine/player.h"
# include "../core/utils.h"

// TODO: add GNL lib

// =========================== Core Game Functions ============================
t_game	*init_game(char *map_path);
int		gameloop(t_game *game);
int		handle_close(t_game *game);
void	free_game(t_game *game);

#endif
