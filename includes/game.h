#ifndef GAME_H
#define GAME_H

// ============= Includes =============

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "stdbool.h"

#include "../libs/mlx/mlx.h"
#include "../libs/libft/libft.h"

#include "structures.h"


// ============= Checker Functions =============

bool 	has_valid_cub_extension(const char *filename);

// ============= Utils =============

int		ft_strcmp(const char *s1, const char *s2);
void	display_error_message(char *msg);

#endif