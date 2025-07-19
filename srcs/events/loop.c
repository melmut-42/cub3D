#include "game.h"

// TODO: fix segfault when lines are too small
static void render_scene(t_game *game);
static void	update_player(t_game *g, t_player *p, t_map *map);
static void render_game(t_game *game);

// * The main game loop function that updates the game state
int gameloop(t_game *game)
{
	if (!should_update(game))
		return (0);

	// Update player position and rotation based on input
	if (game->player.mov_up   || game->player.mov_down  ||
		game->player.mov_left || game->player.mov_right ||
		game->player.rot.x    || game->player.rot.y)
	{
		update_player(game, &game->player, &game->data.map);
	}

	// Render the game state
	render_game(game);
	return (0);
}

static void render_game(t_game *game)
{
	// Render main 3D scene
	render_scene(game);

	// TODO: Render minimap overlay
	//draw_minimap(game);

	// TODO: Render HUD elements
	//draw_hud(game);

	// TODO: Render other game elements
	//draw_elements(game);
}

// * Handles player movement and rotation
static void	update_player(t_game *g, t_player *p, t_map *map)
{
	t_axis strafe;
	double angle;

	strafe.x = -p->dir.y;
	strafe.y = p->dir.x;

	if (p->mov_up)
		attempt_move(map, &p->pos, p->dir.x * p->mov_speed, p->dir.y * p->mov_speed);
	if (p->mov_down)
		attempt_move(map, &p->pos, -p->dir.x * p->mov_speed, -p->dir.y * p->mov_speed);
	if (p->mov_right)
		attempt_move(map, &p->pos, strafe.x * p->mov_speed, strafe.y * p->mov_speed);
	if (p->mov_left)
		attempt_move(map, &p->pos, -strafe.x * p->mov_speed, -strafe.y * p->mov_speed);
	if (p->rot.x)
	{
		angle = p->rot.x * p->sens.x;
		rotate_vector(&g->data, &p->dir, angle);
		rotate_vector(&g->data, &p->plane, angle);
	}
}

// * Casts rays to render the scene
static void render_scene(t_game *game)
{
	t_ray	ray;
	int		screenW;
	int		i;

	i = 0;
	screenW = game->mlx->width;
	while (i < screenW) // Cast rays for each vertical pixel
	{
		cast_ray(game, &ray, i);
		draw_column(game, &ray, i);
		i++;
	}

	// Display the rendered frame in the window
	mlx_put_image_to_window(game->mlx->mlx_ptr,
		game->mlx->win_ptr,
		game->mlx->frame_img.img_ptr,
		0, 0);
}
