#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include "./macros.h"

/**
 * @enum e_directions
 * @brief Enumerates direction identifiers and special texture indices.
 */
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

/** @brief Type alias for millisecond timestamps. */
typedef uint64_t	t_ms;

/**
 * @struct s_draw_util
 * @brief Utility structure for drawing vertical columns of textures.
 */
typedef struct s_draw_util
{
	int		center;
	int		tex_y;
	int		window_y;
	double	tex_pos;
	double	step;
}			t_draw_util;

/**
 * @struct s_img
 * @brief Represents an image/texture loaded via MiniLibX.
 */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
	int		width;
	int		height;
}					t_img;

/**
 * @struct s_column
 * @brief Holds rendering information for a single vertical slice (column).
 */
typedef struct s_column
{
	t_img	*texture;
	int		window_x;
	int		pixel_top;
	int		pixel_bottom;
	int		texture_x;
	int		wall_height;
}					t_column;

/**
 * @struct s_texture
 * @brief Holds all texture resources and color values for the game.
 */
typedef struct s_texture
{
	t_img	doors[NUM_DOOR_FRAMES];
	t_img	textures[NUMBER_DIR];
	char	*door_paths[NUM_DOOR_FRAMES];
	int		ceil_rgb[RGB_CONSTANT];
	int		floor_rgb[RGB_CONSTANT];
	int		ceil_color;
	int		floor_color;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}					t_texture;

/**
 * @struct s_map
 * @brief Represents the loaded map data.
 */
typedef struct s_map
{
	char	**matrix;
	char	*map_path;
	size_t	height;
	size_t	width;
}					t_map;

/**
 * @struct t_axis
 * @brief Represents a 2D vector or point in double precision.
 *
 * @details
 * - Can be used for positions, directions, velocities, and forces in 2D space.
 * - Often paired with vector operations such as addition, subtraction,
 *   normalization, and scalar multiplication.
 */
typedef struct s_axis
{
	double				x;
	double				y;
}					t_axis;

/**
 * @struct t_axis_int
 * @brief Represents a 2D vector or point in integer precision.
 *
 * @details
 * - Useful for pixel coordinates, map grid positions, or any discrete 2D values.
 * - Mirrors t_axis but uses integers instead of doubles.
 */

typedef struct s_axis_int
{
	int				x;
	int				y;
}					t_axis_int;

/**
 * @struct s_vertical
 * @brief Manages vertical movement states like jumping and crouching.
 */
typedef struct s_vertical
{
	double	jump_off;
	double	crouch_off;
	double	crouch_target;
	double	vertical_pos;
	double	vertical_vel;
	bool	in_air;
	bool	in_crouch;
}					t_vertical;

/**
 * @struct s_player
 * @brief Represents the player state and movement.
 */
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

/**
 * @struct s_door
 * @brief Represents a door object in the game world.
 */
typedef struct s_door
{
	t_axis_int	pos;
	t_ms		last_touch;
	double		open;
	bool		is_moving;
	bool		want_open;
}				t_door;

/**
 * @struct s_door_feat
 * @brief Holds door-related data for raycasting calculations.
 */
typedef struct s_door_feat
{
	t_door		*ptr;
	double		open;
	double		perp_dist;
	t_axis_int	pos;
	int			side;
}				t_door_feat;

/**
 * @struct s_weapon
 * @brief Contains weapon state and rendering data.
 */
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
}				t_weapon;

/**
 * @struct s_ray
 * @brief Represents a ray used for raycasting calculations.
 */
typedef struct s_ray
{
	t_door_feat	door_feat;
	t_axis		dir;
	t_axis		side_dist;
	t_axis		delta_dist;
	t_axis_int	pos;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	bool		does_hit;
	bool		is_door;
}					t_ray;

/**
 * @struct t_mlx
 * @brief Contains MiniLibX context and window properties.
 */
typedef struct t_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title;
	int		width;
	int		height;
	t_img	frame_img;

}				t_mlx;

/**
 * @struct s_data
 * @brief Holds global game data, including trigonometric tables and resources.
 */
typedef struct s_data
{
	double		sin_table[NUM_OF_DEGREE];
	double		cos_table[NUM_OF_DEGREE];
	t_map		map;
	t_texture	texture;
}					t_data;

/**
 * @struct s_game
 * @brief The main game structure containing all state information.
 */
typedef struct s_game
{
	t_mlx		*mlx;
	char		*name;
	size_t		door_count;
	t_door		*doors;
	t_weapon	*weapon;
	t_data		data;
	t_player	player;
	t_ms		last_update;
	bool		error_flag;
}				t_game;

#endif
