#ifndef STRUCTURES_H
# define STRUCTURES_H

// ============= Constants =============

#define MAP_FILE_EXTENSION ".cub"


// ============= Enums =============

typedef enum	e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}				t_directions;


// ============= Structures =============

typedef struct s_texture
{
	t_directions	dir;
	char			*path;
	int				rgb[3];
}				t_texture;


typedef struct s_game
{
	char		*name;
	char		*map_path;
	t_texture	texture_list[6];
}				t_game;


#endif
