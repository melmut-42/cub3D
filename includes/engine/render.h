#ifndef RENDER_H
# define RENDER_H

# include "../core/structures.h"

// ==== Raycasting & Columns ====
void	cast_ray(t_game *game, t_ray *ray, int x);
void	draw_texture(t_game *game, t_ray *ray, int x);
void	draw_column(t_game *game, t_ray *ray, int x);
void	rotate_vector(t_data *data, t_axis *vec, double angle);
void	update_player_movement(t_game *game, t_player *p);
int		get_angle_index(double angle);

// ==== HUD & Minimap ====
void	draw_hud(t_game *game);
void	draw_minimap(t_game *game);
void	draw_minimap_rays(t_game *g, t_img *img, t_axis_int offset);
void	draw_weapon(t_game *game);

// ==== MLX & Textures ====
bool	init_mlx(t_game *game, int width, int height, char *title);
bool	init_frame_image(t_game *game);
bool	load_game_textures(t_game *game);
void	mlx_out_txt(t_game *game, int x, int y, char *str);
int		get_pixel_from_img(t_img *img, int x, int y);
t_img	*xpm_to_img(void *mlx, char *path);

#endif
