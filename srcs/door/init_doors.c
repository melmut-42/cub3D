#include "game.h"

static size_t	get_door_count(char **map);
static void		door_ctor(t_door *d, int x, int y);
static void		fill_doors(char **map, t_door *list, size_t cap);

bool	init_doors(t_game *game)
{
	t_door	*door_list;

	game->door_count = get_door_count(game->data.map.matrix);
	if (game->door_count == 0)
	{
		game->doors = NULL;
		return (true);
	}
	door_list = ft_calloc(game->door_count, sizeof(t_door));
	if (!door_list)
	{
		display_error_message(ERR_GAME, true);
		return (false);
	}
	fill_doors(game->data.map.matrix, door_list, game->door_count);
	game->doors = door_list;
	return (true);
}

static size_t	get_door_count(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == DOOR)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	door_ctor(t_door *d, int x, int y)
{
	d->pos.x = x;
	d->pos.y = y;
	d->last_touch = 0;
	d->open = 0.0;
	d->is_moving = false;
	d->want_open = false;
}

static void	fill_doors(char **map, t_door *list, size_t door_count)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (map[i] && k < door_count)
	{
		j = 0;
		while (map[i][j] && k < door_count)
		{
			if (map[i][j] == DOOR)
			{
				door_ctor(&list[k], (int)j, (int)i);
				k++;
			}
			j++;
		}
		i++;
	}
}
