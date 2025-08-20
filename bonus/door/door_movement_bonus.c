#include "game.h"

static double	validate_open(double v);
static size_t	door_frame_from_open(double open);
static void	update_single_door(t_door *door, t_ms now);

t_img	*get_door_texture(t_game *g, const t_door *door)
{
	size_t idx;

	idx = door_frame_from_open(door->open);
	return (&g->data.texture.doors[idx]);
}

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

static double	validate_open(double open)
{
	if (open < 0.0)
		return (0.0);
	if (open > 1.0)
		return (1.0);
	return (open);
}

static size_t	door_frame_from_open(double open)
{
	size_t	idx;
	double	valid_open;

	valid_open = validate_open(open);
	idx = (size_t)(valid_open * (double)(NUM_DOOR_FRAMES - 1) + 0.5);
	if (idx >= NUM_DOOR_FRAMES)
		idx = NUM_DOOR_FRAMES - 1;
	return (idx);
}

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


