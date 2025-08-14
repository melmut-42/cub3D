#include "game.h"

static void render_scene(t_game *game);

// * The main game loop function that updates the game state
int gameloop(t_game *game)
{
	if (!should_update(game))
		return (0);

	// Update player position and rotation based on input
	if (game->player.movement[W]   || game->player.movement[S]  ||
		game->player.movement[A] || game->player.movement[D] ||
		game->player.rot.x || game->player.rot.y)
	{
		update_player_movement(game, &game->player);
	}

	// Render the game state
	render_scene(game);
	return (0);
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
