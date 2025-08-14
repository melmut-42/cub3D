#include "game.h"

static size_t	count_doors_in_map(char **matrix, size_t height);
static void		set_door(t_door *door, int x, int y);
static void		set_all_doors(t_game *game);

bool	init_doors(t_game *game)
{
	size_t	door_count;

	door_count = count_doors_in_map(
			game->data.map.matrix, game->data.map.height);
	game->door_count = door_count;
	if (door_count == 0)
	{
		game->doors = NULL;
		return (true);
	}
	game->doors = ft_calloc(door_count, sizeof(t_door));
	if (!game->doors)
	{
		display_error_message(ERR_GAME, true);
		return (false);
	}
	set_all_doors(game);
	return (true);
}

static void	set_all_doors(t_game *game)
{
	t_axis_int	pos;
	size_t		i;

	i = 0;
	pos.y = 0;
	while ((size_t)pos.y < game->data.map.height)
	{
		pos.x = 0;
		while (game->data.map.matrix[pos.y][pos.x])
		{
			if (game->data.map.matrix[pos.y][pos.x] == DOOR)
				set_door(&game->doors[i++], pos.x, pos.y);
			pos.x++;
		}
		pos.y++;
	}
}

static void	set_door(t_door *door, int x, int y)
{
	door->pos.x = x;
	door->pos.y = y;
	door->is_moving = false;
	door->want_open = false;
}

static size_t	count_doors_in_map(char **matrix, size_t height)
{
	size_t	count;
	size_t	y;
	size_t	x;

	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (matrix[y][x])
		{
			if (matrix[y][x] == DOOR)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
