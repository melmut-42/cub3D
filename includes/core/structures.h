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

# define COMMA ','
# define MAP_FILE_EXTENSION ".cub"

# define DIR_SET "NSWE"
# define SPACE_SET " \n\t\v\f\r"

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_SPACE 32
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SHIFT 65505
# define KEY_UP 65364
# define KEY_DOWN 65362
# define KEY_CTRL_L 65507
# define KEY_CTRL_R 65508

# define MINIMAP_RADIUS 100
# define MINIMAP_SCALE 0.2
# define MINIMAP_FOV 90
# define RAY_COUNT 120
# define RAY_MAX_LEN 5.0
# define RAY_STEP_SIZE 0.05

# define MINIMAP_TILE_SIZE 4
# define MINIMAP_PLAYER_SIZE 7

typedef enum e_directions
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
	int				screen_x;
	int				pixel_top;
	int				pixel_bottom;
	int				texture_x;
	int				wall_height;
}					t_column;

typedef struct s_texture
{
	t_img			textures[NUMBER_DIR];
	int				ceil_rgb[RGB_CONSTANT];
	int				floor_rgb[RGB_CONSTANT];
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
	double	jump_off;
	double	crouch_off;
	double	crouch_target;
	double	vertical_pos;
	double	vertical_vel;
	bool	in_crouch;
	bool	in_air;
}					t_vertical;

typedef struct s_player
{
	int			movement[NUMBER_DIR];
	double		mov_speed;
	double		pitch_angle;
	t_axis		dir;
	t_axis		plane;
	t_axis		pos;
	t_axis		rot;
	t_axis		sens;
	t_vertical	vertical;
}				t_player;

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
	t_axis			dir;
	t_axis			map;
	t_axis			side_dist;
	t_axis			delta_dist;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				side;
	bool			does_hit;
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
	double			cos_table[NUM_OF_DEGREE];
	double			sin_table[NUM_OF_DEGREE];
	t_texture		texture;
	t_map			map;
}					t_data;

typedef struct s_game
{
	t_mlx		*mlx;
	t_data		data;
	t_player	player;
	t_weapon	weapon;
	char		*name;
	t_ms		last_update;
	bool		error_flag;
}				t_game;

#endif
