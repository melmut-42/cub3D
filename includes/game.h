#ifndef GAME_H
#define GAME_H

// ============= Includes =============

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "stdbool.h"

#include "get_next_line.h"
#include "../libs/mlx/mlx.h"
#include "../libs/libft/libft.h"


// ============= Constants =============

#define MAP_FILE_EXTENSION ".cub"


// ============= Checker Functions =============

bool has_valid_cub_extension(const char *filename);

#endif