#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h> 
# include <stddef.h>

// ============= Window Constants =============

# define WIN_TITLE	"Cub3D"
# define WIN_WIDTH	1024
# define WIN_HEIGHT	768

// TODO: Check whether this is a macro or not (forbidden)
# define MID_POINT_X	WIN_WIDTH / 2
# define MID_POINT_Y	WIN_HEIGHT / 2
# define PLAYER_MARGIN 0.25

# define TARGET_FPS	100

// ============= Game Physics Constants =============

# define W	0
# define S	1
# define D	2
# define A	3

# define SENS_X	0.05
# define SENS_Y	0.6

# define INITIAL_SPEED	0.04

// ============= Rotation Constants =============

# define NUM_OF_DEGREE	360

# define MAX_PITCH	500.0
# define MIN_PITCH	-500.0
# define MAX_VERTICAL_DELTA	50

// ============= Vertical Constants =============

# define GRAVITY        90.0
# define JUMP_VELOCITY  60.0
# define JUMP_SCALE     5

# define CROUCH_SCALE		40.0
# define CROUCH_OUT_SPEED	150.0

// ============= Map Elements =============

# define NPOS	-1

# define NUMBER_DIR	4

# define RGB_CONSTANT	3
# define RGB_MIN_VAL	0
# define RGB_MAX_VAL	255

# define NORTH_ABB		"NO"
# define SOUTH_ABB		"SO"
# define WEST_ABB		"WE"
# define EAST_ABB		"EA"
# define FLOOR_ABB		"F"
# define CEILING_ABB	"C"

# define GROUND		'0'
# define WALL		'1'
# define VISITED	'X'

# define COMMA	','
# define MAP_FILE_EXTENSION	".cub"

# define DIR_SET	"NSWE"
# define SPACE_SET	" \n\t\v\f\r"


// ============= Key Codes =============

# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_SPACE	32
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_SHIFT	65505
# define KEY_UP		65364
# define KEY_DOWN	65362
# define KEY_CTRL_L	65507
# define KEY_CTRL_R	65508

// ================= Minimap Constants =================

#define MINIMAP_RADIUS     100
#define MINIMAP_SCALE      0.2
#define MINIMAP_FOV        90
#define RAY_COUNT          120
#define RAY_MAX_LEN        5.0
#define RAY_STEP_SIZE      0.05

#define MINIMAP_TILE_SIZE 4
#define MINIMAP_PLAYER_SIZE 7


// ======================================= Enums =======================================

// * Defines the possible directions for map parsing and texture loading
typedef enum	e_directions
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	NONE
}					t_dir;

// ======================================= Structures =======================================

typedef uint64_t t_ms;

// * Represents an image in memory with its properties
typedef struct	s_img
{
	void			*img_ptr;		// pointer to image in memory
	char			*addr;			// pointer to the image data
	int				bpp;			// bits per pixel
	int				endian;			// endianess of the image data
	int				line_len;		// length of a line in bytes
	int				width;			// width of the image
	int				height;			// height of the image
}					t_img;

// * Represents a column of pixels in the 3D rendering
typedef struct s_column
{
	t_img			*texture;       // Texture to sample from
	int				screen_x;       // Screen column (X) being rendered
	int				pixel_top;      // Start of the wall slice on screen
	int				pixel_bottom;   // End of the wall slice on screen
	int				texture_x;      // X coordinate in the texture
	int				wall_height;    // Projected height of the wall
}					t_column;

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
	size_t			width;
	char			*map_path;
	char			**matrix;
}					t_map;

// * Represents a 2D axis with x and y coordinates
typedef struct s_axis
{
	double				x;
	double				y;
}					t_axis;

// * Represents a 2D axis with x and y coordinates as integer
typedef struct s_axis_int
{
	int				x;
	int				y;
}					t_axis_int;

// * Represents the vertical state of the player
typedef struct		s_vertical
{
	bool	in_air;
	bool	in_crouch;
	double  jump_off;
	double  crouch_off;
	double  crouch_target;
	double	vertical_pos;
	double	vertical_vel;
}					t_vertical;

// * Holds direction, position, movement flags, and camera settings
typedef struct	s_player
{
	int			movement[NUMBER_DIR];
	double		mov_speed;		// movement speed
	double		pitch_angle;	// vertical look angle (up/down)
	t_axis		dir;			// camera direction vector
	t_axis		plane;			// camera plane vector
	t_axis		pos;			// player position in the map
	t_axis		rot;			// rotation vector
	t_axis		sens;			// sensitivity vector
	t_vertical	vertical;		// vertical attributes
}				t_player;

// * Ray structure for raycasting
typedef struct s_ray
{
	t_axis			dir;				// ray direction
	t_axis			map;				// which coordinates of the map we are in
	t_axis			side_dist;			// length of ray from current pos to next x or y-side
	t_axis			delta_dist;			// length of ray from one x or y-side to next x or y-side
	double			perp_wall_dist;		// distance to wall (corrected)
    int     		step_x;      		// Direction to step in x: +1 (east) or –1 (west)
    int     		step_y;         	// Direction to step in y: +1 (south) or –1 (north)
	bool			does_hit;			// was there a wall hit?
	int				side;				// was a NS or EW wall hit? 0 = vertical (NS), 1 = horizontal (EW)
}					t_ray;

// * Main structure for the MLX window and images
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

// * Main game data structure regarding textures and tables
typedef	struct	s_data
{
	t_map			map;
	t_texture		texture;
	double			cos_table[NUM_OF_DEGREE];
	double			sin_table[NUM_OF_DEGREE];
}					t_data;

// * Main game structure that holds all game-related data
typedef struct s_game
{
	char		*name;
	bool		error_flag;
	t_ms		last_update;
	t_mlx		*mlx;
	t_data		data;
	t_player	player;
}				t_game;

#endif
