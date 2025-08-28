#ifndef MACROS_H
# define MACROS_H

// ==== Window ====
# define WIN_TITLE		"Cub3D"
# define WIN_WIDTH		1024
# define WIN_HEIGHT		768
# define MID_POINT_X 	512
# define MID_POINT_Y 	384

// ==== Player ====
# define PLAYER_MARGIN	0.25
# define INITIAL_SPEED	0.04
# define SENS_X 		0.025
# define SENS_Y 		0.3
# define NUM_OF_DEGREE	360

# define MIN_PITCH			-500.0
# define MAX_PITCH			500.0
# define MAX_VERTICAL_DELTA	50
# define GRAVITY			90.0
# define JUMP_VELOCITY		60.0
# define JUMP_SCALE			5
# define CROUCH_SCALE		40.0
# define CROUCH_OUT_SPEED	150.0

// ==== Controls ====
# define W 			0
# define S 			1
# define D 			2
# define A 			3
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

// ==== Map & Game Constants ====
# define NPOS				-1
# define NUMBER_DIR			4
# define INF_DIST			1e30
# define TARGET_FPS			100
# define DIR_SET			"NSWE"
# define SPACE_SET			" \n\t\v\f\r"
# define GROUND				'0'
# define WALL				'1'
# define VISITED			'X'
# define DOOR				'D'
# define COMMA				','
# define MAP_FILE_EXTENSION	".cub"
# define NORTH_ABB			"NO"
# define SOUTH_ABB			"SO"
# define WEST_ABB			"WE"
# define EAST_ABB			"EA"
# define FLOOR_ABB			"F"
# define CEILING_ABB		"C"

// ==== Colors ====
# define COLOR_RED		0xFF0000
# define COLOR_GREY		0x222222
# define COLOR_PINK		0xff00ff
# define COLOR_GREEN	0x40ff00
# define COLOR_WHITE	0xFFFFFF
# define COLOR_BLACK	0x000000
# define COLOR_YELLOW	0xCCCC66
# define COLOR_OFF_GREY	0x555555

# define RGB_CONSTANT	3
# define RGB_MIN_VAL	0
# define RGB_MAX_VAL	255

// ==== Minimap ====
# define MINIMAP_TILE_SIZE		6
# define MINIMAP_PLAYER_SIZE	4
# define MINIMAP_RADIUS			65
# define MINIMAP_SCALE			0.1
# define MINIMAP_FOV			90

// ==== Rays ====
# define RAY_COUNT		120
# define RAY_MAX_LEN	3
# define RAY_STEP_SIZE	0.05

// ==== Weapon ====
# define WEAPON_PATH	"textures/sprites/karambit.xpm"

// ==== Doors ====
# define NUM_DOOR_FRAMES	5
# define INTERACT_STEP		1.8
# define MIN_DOOR_INT_DIST	0.25
# define DOOR_SPEED			0.2

# define DOOR_FRAME_0	"textures/sprites/door0.xpm"
# define DOOR_FRAME_1	"textures/sprites/door1.xpm"
# define DOOR_FRAME_2	"textures/sprites/door2.xpm"
# define DOOR_FRAME_3	"textures/sprites/door3.xpm"
# define DOOR_FRAME_4	"textures/sprites/door4.xpm"

#endif
