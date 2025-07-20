#include "game.h"

// TODO: fix segfault when lines are too small
static void render_scene(t_game *game);
static void render_game(t_game *game);

// * The main game loop function that updates the game state
int gameloop(t_game *game)
{
	if (!should_update(game))
		return (0);

	// Update player position and rotation based on input
	if (game->player.mov_up   || game->player.mov_down  ||
		game->player.mov_left || game->player.mov_right ||
		game->player.rot.x    || game->player.rot.y ||
		game->player.vertical.in_air)
	{
		update_player_movement(game, &game->player, &game->data.map);
	}
	
	update_player_vertical(&game->player, 0.016);
	update_player_rise(&game->player, 0.016);
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
