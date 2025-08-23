#ifndef BONUS_H
# define BONUS_H

# include "structures.h"

# define KEY_E		101
# define KEY_SPACE	32

# define KEY_UP		65364
# define KEY_DOWN	65362

# define KEY_SHIFT	65505
# define KEY_CTRL_L	65507

# define MINIMAP_TILE_SIZE		6
# define MINIMAP_PLAYER_SIZE	4

# define MINIMAP_RADIUS	65
# define MINIMAP_SCALE	0.1
# define MINIMAP_FOV	90
# define RAY_COUNT		120
# define RAY_MAX_LEN	3
# define RAY_STEP_SIZE	0.05

# define MID_POINT_X 512
# define MID_POINT_Y 384

# define COLOR_RED		0xFF0000
# define COLOR_GREY		0x222222
# define COLOR_PINK		0xff00ff
# define COLOR_GREEN	0x40ff00
# define COLOR_WHITE	0xFFFFFF
# define COLOR_BLACK	0x000000
# define COLOR_YELLOW	0xCCCC66
# define COLOR_OFF_GREY	0x555555

# define WEAPON_TEXT	"textures/sprites/karambit.xpm"

void	draw_hud(t_game *game);
void	mlx_out_txt(t_game *game, int x, int y, char *str);
void	draw_minimap(t_game *game);
void	draw_minimap_rays(t_game *g, t_img *img, t_axis_int offset);
void	draw_weapon(t_game *game);
int		get_pixel_from_img(t_img *img, int x, int y);
t_img	*xpm_to_img(void *mlx, char *path);

bool	is_moving(t_game *game);
bool	is_jumping(t_game *game);
void	stand_up(t_player *p, double dt);
void	jump_event(t_player *p, double dt);

bool	init_weapon(t_game *game);
void	weapon_ctor(t_weapon *weapon);
float	lerp(float start, float end, float t);
int		handle_mouse_click(int button, int x, int y, t_game *game);

bool	init_doors(t_game *game);
void	update_doors(t_game *game);
void	handle_door_interact(t_game *g);
t_img	*get_door_texture(t_game *g, const t_door *door);
t_door	*get_the_door(t_game *g, int x, int y);
void	update_ray_door(t_game *game, t_ray *ray, int map_y, int map_x);
void	start_draw_doors(t_game *game, t_ray *ray, int x);

#endif
