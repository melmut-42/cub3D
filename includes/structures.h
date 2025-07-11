#ifndef STRUCTURES_H
# define STRUCTURES_H

// ============= Constants =============

# define BUFFER_SIZE 1024
# define MAP_FILE_EXTENSION ".cub"

# define NORTH_ABB "NO"
# define SOUTH_ABB "SO"
# define WEST_ABB "WE"
# define EAST_ABB "EA"
# define FLOOR_ABB "F"
# define CEILING_ABB "C"

# define SPACE_SET "\n\t\v\f\r "

// ============= Enums =============

typedef enum e_directions
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
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_rgb[3];
	int			ceil_rgb[3];
}				t_texture;

typedef struct s_map
{
	char		*map_path;
	char		**matrix;
}				t_map;

typedef	struct	s_data
{
	t_map		map;
	t_texture	texture;
}				t_data;


typedef struct s_game
{
	char		*name;
	t_data		data;
}				t_game;

#endif
