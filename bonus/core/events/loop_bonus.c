#include "game.h"
#include "bonus.h"

static void render_scene(t_game *game);
static void render_game(t_game *game);

// * The main game loop function that updates the game state
int gameloop(t_game *game)
{
	if (!should_update(game))
		return (0);

	// Update player position and rotation based on input
	if (game->player.movement[W]   || game->player.movement[S]  ||
		game->player.movement[A] || game->player.movement[D] ||
		game->player.rot.x || game->player.rot.y ||
		game->player.vertical.in_air)
	{
		update_player_movement(game, &game->player, &game->data.map);
	}
	
	jump_event(&game->player, 0.016);
	stand_up(&game->player, 0.016);

	// Render the game state
	render_game(game);
	return (0);
}

static void render_game(t_game *game)
{
	// Render main 3D scene
	render_scene(game);

	// Render minimap with rays
	draw_minimap(game);

	// Render FPS counter, coordinates, and direction
	draw_hud(game);

	// Render the weapon with shaking effect
	draw_weapon(game);

	// TODO: Render other game elements (like doors)
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
