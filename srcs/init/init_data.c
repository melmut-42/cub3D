#include "game.h"

bool	init_data(t_game *game)
{
	if (!process_file_data(game, game->data.map.matrix));
		return (false);
	return (true);
}

static bool	process_file_data(t_game *game, const char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		display_error_message(FILE_ERR, true);
		return (false);
	}
	if (!process_texture_data(game, &game->data.texture, fd))
		return (false);
	if (!process_map_data(game, &game->data.map, fd))
		return (false);
	return (true);
}
