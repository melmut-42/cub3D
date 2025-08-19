#ifndef BONUS_H
# define BONUS_H

# include "structures.h"

# define INF_DIST 1e30
# define TEXT_COLOR 0xFFFFFF

void	draw_hud(t_game *game);
void	mlx_out_txt(t_game *game, int x, int y, char *str);
void	draw_minimap(t_game *game);
void	draw_minimap_rays(t_game *g, t_img *img, t_axis_int offset);
void	draw_weapon(t_game *game);
int		get_pixel_from_img(t_img *img, int x, int y);
t_img	*xpm_to_img(void *mlx, char *path);
bool	is_moving(t_game *game);
bool	is_jumping(t_game *game);
void	weapon_ctor(t_weapon *weapon);
int		handle_mouse_click(int button, int x, int y, t_game *game);
void	stand_up(t_player *p, double dt);
void	jump_event(t_player *p, double dt);

bool	init_doors(t_game *game);
void	update_doors(t_game *game);
void	handle_door_interact(t_game *g);
t_img	*get_door_texture(t_game *g, const t_door *door);
t_door	*get_the_door(t_game *g, int x, int y);
void	update_ray_door(t_game *game, t_ray *ray, int map_y, int map_x);

void	start_draw_doors(t_game *game, t_ray *ray, int x);

#endif
