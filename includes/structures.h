#ifndef STRUCTURES_H
# define STRUCTURES_H

// ============= Constants =============

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define WIN_TITLE "Cub3D"
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define NPOS -1

# define NUMBER_DIR 4

# define RGB_CONSTANT 3
# define RGB_MIN_VAL 0
# define RGB_MAX_VAL 255

# define MAP_FILE_EXTENSION ".cub"

# define COMMA ','

# define NORTH_ABB "NO"
# define SOUTH_ABB "SO"
# define WEST_ABB "WE"
# define EAST_ABB "EA"
# define FLOOR_ABB "F"
# define CEILING_ABB "C"

# define NEWLINE "\n"
# define SPACE_SET "\n\t\v\f\r "


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

typedef enum	e_err_code
{
	MALLOC_ERR,
	RENDER_ERR
}				t_err_code;

// ============= Structures =============

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			ceil_rgb[RGB_CONSTANT];
	int			floor_rgb[RGB_CONSTANT];
}				t_texture;

typedef struct s_map
{
	size_t		height;
	char		*map_path;
	char		**matrix;
}				t_map;

typedef struct	t_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*title;
	int			width;
	int			height;
}				t_mlx;

typedef	struct	s_data
{
	t_map		map;
	t_texture	texture;
}				t_data;


typedef struct s_game
{
	char		*name;
	t_data		data;
	t_mlx		*mlx;
	bool		error_flag;
}				t_game;

#endif
