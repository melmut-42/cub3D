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

# define GROUND '0'
# define WALL '1'
# define VISITED 'X'


# define DIR_SET "NSWE"
# define SPACE_SET " \n\t\v\f\r"


// ============= Key Codes =============

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// ============= Enums =============

// * Defines the possible directions for map parsing
typedef enum	e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	NONE
}					t_directions;

// * Defines errors for robust error handling
typedef enum	e_err_code
{
	MALLOC_ERR,
	RENDER_ERR
}				t_err_code;

// ============= Structures =============

// * Represents an image in memory with its properties
typedef struct	s_img
{
	void		*img_ptr;		// pointer to image in memory
	char		*addr;			// pointer to the image data
	int			bpp;			// bits per pixel
	int			endian;			// endianess of the image data
	int			line_len;		// length of a line in bytes
	int			width;			// width of the image
	int			height;			// height of the image
}				t_img;

// * Represents a texture with paths for different directions and RGB values for ceiling and floor
typedef struct s_texture
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				ceil_rgb[RGB_CONSTANT];
	int				floor_rgb[RGB_CONSTANT];
	t_img			textures[NUMBER_DIR];		// array of textures for different directions
}					t_texture;

// * Represents a map with height, path to the map file, and a 2D matrix of characters
typedef struct s_map
{
	size_t			height;
	char			*map_path;
	char			**matrix;
}					t_map;

// * Represents a 2D axis with x and y coordinates
typedef struct s_axis
{
	double				x;
	double				y;
}					t_axis;

// * Holds direction, position, movement flags, and camera settings
typedef struct	s_player
{
	int			mov_up;        	// move forward flag
	int			mov_down;      	// move backward flag
	int			mov_left;      	// move left flag (strafe)
	int			mov_right;     	// move right flag (strafe)
	double		mov_speed;		// movement speed
	double		pitch_angle;	// vertical look angle (up/down)
	t_axis		dir;			// camera direction vector
	t_axis		plane;			// camera plane vector
	t_axis		pos;			// player position in the map
	t_axis		rot;			// rotation vector
	t_axis		sens;			// sensitivity vector
}				t_player;

typedef struct	t_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*title;
	int			width;
	int			height;
	t_img		frame_img;		// image structure for the frame (main screen buffer)
	t_img		minimap_img;	// image structure for the minimap
}				t_mlx;

typedef	struct	s_data
{
	t_map			map;
	t_texture		texture;
}					t_data;

typedef struct s_game
{
	char		*name;
	t_data		data;
	t_mlx		*mlx;
	t_player	player;
	bool		error_flag;
}				t_game;

#endif
