#include "game.h"

static size_t	get_door_count(char **map);
static void		door_ctor(t_door *d, int x, int y);
static void		fill_doors(char **map, t_door *list, size_t cap);

/**
 * @brief Initializes all doors in the game by scanning the map and allocating memory.
 *
 * @details
 * - Counts doors in the map using get_door_count().
 * - Allocates and fills a list of door structures.
 * - Handles the case where no doors are present.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true on successful initialization, false on allocation failure.
 */
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

/**
 * @brief Counts the total number of doors in the map matrix.
 *
 * @param map (char **): The 2D map matrix.
 *
 * @return (size_t): The total number of doors found.
 */
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

/**
 * @brief Constructs and initializes a single door structure.
 *
 * @details
 * - Sets position coordinates.
 * - Resets timing and state fields to defaults.
 *
 * @param d (t_door *): Pointer to the door structure to initialize.
 * @param x (int): X-coordinate of the door in the map.
 * @param y (int): Y-coordinate of the door in the map.
 *
 * @return void
 */
static void	door_ctor(t_door *d, int x, int y)
{
	d->pos.x = x;
	d->pos.y = y;
	d->last_touch = 0;
	d->open = 0.0;
	d->is_moving = false;
	d->want_open = false;
}

/**
 * @brief Populates the door list with all doors found in the map.
 *
 * @details
 * - Iterates through the map matrix.
 * - Calls door_ctor() for each door found.
 * - Stops when all doors are initialized or the map ends.
 *
 * @param map (char **): The 2D map matrix.
 * @param list (t_door *): Pre-allocated array of door structures.
 * @param door_count (size_t): Total number of doors to fill.
 *
 * @return void
 */
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
