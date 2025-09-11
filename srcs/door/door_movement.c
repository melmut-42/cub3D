#include "game.h"

static double	validate_open(double v);
static size_t	door_frame_from_open(double open);
static void		update_single_door(t_door *door, t_ms now);

/**
 * @brief Retrieves the correct door texture based on its open ratio.
 *
 * @details
 * - Uses door_frame_from_open() to convert the ratio into a frame index.
 * - Returns a pointer to the texture in the game's texture array.
 *
 * @param g (t_game *): Pointer to the game instance containing textures.
 * @param door (const t_door *): Pointer to the door whose texture is requested.
 *
 * @return (t_img *): Pointer to the door texture.
 */
t_img	*get_door_texture(t_game *g, const t_door *door)
{
	size_t	idx;

	idx = door_frame_from_open(door->open);
	return (&g->data.texture.doors[idx]);
}

/**
 * @brief Updates all doors in the game world.
 *
 * @details
 * - Gets the current timestamp.
 * - Iterates through every door in the game.
 * - Calls update_single_door() for each door to process movement and state.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return void
 */
void	update_doors(t_game *game)
{
	t_ms	now;
	size_t	i;

	now = get_timestamp(game);
	i = 0;
	while (i < game->door_count)
	{
		update_single_door(&game->doors[i], now);
		i++;
	}
}

/**
 * @brief Clamps a door's open value to the valid range [0.0, 1.0].
 *
 * @param v (double): The raw open ratio to clamp.
 *
 * @return (double): The validated open ratio within [0.0, 1.0].
 */
static double	validate_open(double open)
{
	if (open < 0.0)
		return (0.0);
	if (open > 1.0)
		return (1.0);
	return (open);
}

/**
 * @brief Converts a normalized open ratio into a texture frame index.
 *
 * @details
 * - Multiplies the clamped ratio by NUM_DOOR_FRAMES to pick a frame.
 * - Ensures the index never exceeds the maximum frame count.
 *
 * @param open (double): The door's normalized open ratio.
 *
 * @return (size_t): The corresponding texture frame index.
 */
static size_t	door_frame_from_open(double open)
{
	size_t	idx;
	double	valid_open;

	valid_open = validate_open(open);
	idx = (size_t)floor(valid_open * (double)NUM_DOOR_FRAMES);
	if (idx >= NUM_DOOR_FRAMES)
		idx = NUM_DOOR_FRAMES - 1;
	return (idx);
}

/**
 * @brief Updates the movement and state of a single door.
 *
 * @details
 * - Calculates time delta since last update to control movement speed.
 * - Increments or decrements the door's open value depending on want_open.
 * - Stops movement when the door is fully open (1.0) or fully closed (0.0).
 * - Updates last_touch to the current timestamp after movement.
 *
 * @param door (t_door *): Pointer to the door instance being updated.
 * @param now (t_ms): Current timestamp in milliseconds.
 *
 * @return void
 */
static void	update_single_door(t_door *door, t_ms now)
{
	double	delta;
	double	step;

	if (!door->is_moving)
		return ;
	delta = (now - door->last_touch) / 1000.0;
	if (delta <= 0.25)
		return ;
	step = DOOR_SPEED;
	if (door->want_open)
		door->open = validate_open(door->open + step);
	else
		door->open = validate_open(door->open - step);
	if (door->open == 0.0 || door->open == 1.0)
		door->is_moving = false;
	door->last_touch = now;
}
