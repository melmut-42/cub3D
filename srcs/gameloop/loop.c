#include "game.h"

// * Handles player movement
void	update_player(t_game *game)
{
	// ! PLACEHOLDER FUNCTION
	(void)game;
	// - Update player position based on movement flags
	// - Update player rotation based on rotation flags
	// - Ensure player stays within map bounds
}

// * The main game loop function that updates the game state
int	gameloop(t_game *game)
{
	if (game->player.mov_up || game->player.mov_down ||
		game->player.mov_left || game->player.mov_right ||
		game->player.rot_left || game->player.rot_right)
	{
		// Update player position and rotation based on input
		update_player(game); // TODO: implement this function

		// Render the game state
//		render_game(game); // TODO: implement this function
	}
	else
	{
		// If no input, just render the current state
//		render_game(game);
	}

	return (0);
}
