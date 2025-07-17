#include "game.h"

static void render_scene(t_game *game);
static void	update_player(t_game *game);
static void render_game(t_game *game);

// * The main game loop function that updates the game state
int gameloop(t_game *game)
{
    if (!should_update(game))
        return (0);
    if (game->player.mov_up   || game->player.mov_down  ||
        game->player.mov_left || game->player.mov_right ||
        game->player.rot.x    || game->player.rot.y)
    {
        // Update player position and rotation based on input
        update_player(game);
    }
    // Render the game state
    render_game(game);
    return (0);
}

// * Handles player movement
static void	update_player(t_game *game)
{
	// ! PLACEHOLDER FUNCTION
	(void)game;
	// - Update player position based on movement flags
	// - Update player rotation based on rotation flags
	// - Ensure player stays within map bounds
}

static void render_game(t_game *game)
{
    // Render main 3D scene
    render_scene(game);

    // TODO: Render minimap overlay
    //draw_minimap(game);

    // Present frame buffer to window
    //mlx_put_image_to_window(
    //    game->mlx->mlx_ptr,
    //    game->mlx->win_ptr,
    //    game->mlx->frame_img.img_ptr,
    //    0,
    //    0
    //);
}

static void render_scene(t_game *game)
{
	int		i;
    t_ray	ray;
    int		screenW;

	screenW = game->mlx->width;
	i = 0;
	while (i < screenW)
	{
		cast_ray(game, &ray, i);
        // draw_column(game, &ray, i); // TODO: Implement later
		i++;
	}
}
