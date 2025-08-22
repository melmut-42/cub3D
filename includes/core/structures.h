#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

# define WIN_TITLE "Cub3D"
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define MID_POINT_X 512
# define MID_POINT_Y 384
# define PLAYER_MARGIN 0.25

# define TARGET_FPS 100

# define W 0
# define S 1
# define D 2
# define A 3

# define SENS_X 0.025
# define SENS_Y 0.3

# define INITIAL_SPEED 0.04

# define NUM_OF_DEGREE 360

# define MIN_PITCH -500.0
# define MAX_PITCH 500.0
# define MAX_VERTICAL_DELTA 50

# define INF_DIST 1e30

# define GRAVITY 90.0
# define JUMP_VELOCITY 60.0
# define JUMP_SCALE 5

# define CROUCH_SCALE 40.0
# define CROUCH_OUT_SPEED 150.0

# define NPOS -1

# define NUMBER_DIR 4

# define RGB_CONSTANT 3
# define RGB_MIN_VAL 0
# define RGB_MAX_VAL 255

# define NORTH_ABB "NO"
# define SOUTH_ABB "SO"
# define WEST_ABB "WE"
# define EAST_ABB "EA"
# define FLOOR_ABB "F"
# define CEILING_ABB "C"

# define GROUND '0'
# define WALL '1'
# define VISITED 'X'
# define DOOR 'D'

# define COMMA ','
# define MAP_FILE_EXTENSION ".cub"

# define DIR_SET "NSWE"
# define SPACE_SET " \n\t\v\f\r"


// ============= Key Codes =============

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_E		101
# define KEY_SPACE	32

# define KEY_UP		65364
# define KEY_DOWN	65362
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

# define KEY_SHIFT	65505
# define KEY_CTRL_L	65507
# define KEY_ESC	65307

// ================= Minimap Constants =================

#define MINIMAP_RADIUS 65
#define MINIMAP_SCALE 0.1
#define MINIMAP_FOV 90
#define RAY_COUNT 120
#define RAY_MAX_LEN 3
#define RAY_STEP_SIZE 0.05

#define MINIMAP_TILE_SIZE 6
#define MINIMAP_PLAYER_SIZE 4

// ================= Door Constants =================

# define NUM_DOOR_FRAMES 5
# define INTERACT_STEP 1.8
# define MIN_DOOR_INT_DIST 0.25
# define DOOR_SPEED 0.2

# define DOOR_FRAME_0 "textures/test_pack/door0.xpm"
# define DOOR_FRAME_1 "textures/test_pack/door1.xpm"
# define DOOR_FRAME_2 "textures/test_pack/door2.xpm"
# define DOOR_FRAME_3 "textures/test_pack/door3.xpm"
# define DOOR_FRAME_4 "textures/test_pack/door4.xpm"

// ======================================= Enums =======================================

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

typedef uint64_t	t_ms;

typedef struct	s_draw_util
{
	int		center;
	int		tex_y;
	int		window_y;
	double	tex_pos;
	double	step;
}			t_draw_util;

typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				endian;
	int				line_len;
	int				width;
	int				height;
}					t_img;

typedef struct s_column
{
	t_img			*texture;
	int				window_x;
	int				pixel_top;
	int				pixel_bottom;
	int				texture_x;
	int				wall_height;
}					t_column;

typedef struct s_texture
{
	t_img			doors[NUM_DOOR_FRAMES];
	t_img			textures[NUMBER_DIR];
	char			*door_paths[NUM_DOOR_FRAMES];
	int				ceil_rgb[RGB_CONSTANT];
	int				floor_rgb[RGB_CONSTANT];
	int				ceil_color;
	int				floor_color;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
}					t_texture;

typedef struct s_map
{
	char			**matrix;
	char			*map_path;
	size_t			height;
	size_t			width;
}					t_map;

typedef struct s_axis
{
	double				x;
	double				y;
}					t_axis;

typedef struct s_axis_int
{
	int				x;
	int				y;
}					t_axis_int;

typedef struct s_vertical
{
	double  jump_off;
	double  crouch_off;
	double  crouch_target;
	double	vertical_pos;
	double	vertical_vel;
	bool	in_air;
	bool	in_crouch;
}					t_vertical;

typedef struct s_player
{
	t_vertical	vertical;
	int			movement[NUMBER_DIR];
	t_axis		dir;
	t_axis		plane;
	t_axis		pos;
	t_axis		rot;
	t_axis		sens;
	double		mov_speed;
	double		pitch_angle;
}				t_player;

typedef struct s_door
{
	t_axis_int	pos;
	t_ms		last_touch;
	double		open;
	bool		is_moving;
	bool		want_open;
}				t_door;

typedef struct s_door_feat
{
	t_door		*ptr;
	double		open;
	double		perp_dist;
	t_axis_int	pos;
	int			side;
}				t_door_feat;

typedef struct s_weapon
{
	t_img	*weapon_img;
	int		frame_count;
	int		jump_frame;
	int		shake_offset_x;
	int		shake_offset_y;
	int		shake_direction_x;
	int		shake_direction_y;
	int		weapon_base_y;
	bool	load_attempted;
}				t_weapon;

typedef struct s_ray
{
	t_door_feat		door_feat;
	t_axis			dir;
	t_axis			side_dist;
	t_axis			delta_dist;
	t_axis_int		pos;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	bool			does_hit;
	bool			is_door;
}					t_ray;

typedef struct t_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*title;
	int			width;
	int			height;
	t_img		frame_img;

}				t_mlx;

typedef struct s_data
{
	double			sin_table[NUM_OF_DEGREE];
	double			cos_table[NUM_OF_DEGREE];
	t_map			map;
	t_texture		texture;
}					t_data;

typedef struct s_game
{
	t_mlx		*mlx;
	char		*name;
	size_t		door_count;
	t_door		*doors;
	t_weapon	weapon;
	t_data		data;
	t_player	player;
	t_ms		last_update;
	bool		error_flag;
}				t_game;

#endif
