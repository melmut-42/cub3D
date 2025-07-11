#include "game.h"

t_game *init_game(char *map_path)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		display_error_message(GAME_ERR, true);
		return (NULL);
	}
	game->data.map.map_path = map_path;
	if (!init_data(game))
	{
		// TODO: Implement the free function that frees every allocated fields
		return (NULL);
	}
}