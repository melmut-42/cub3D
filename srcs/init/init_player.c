#include "game.h"

static void	update_dir(t_directions dir, t_axis *dir_vector);
static void	update_pos(t_axis *pos, t_axis new_pos, int *x, int *y);
static bool	set_player(t_game *game, t_player *player);
static bool	update_player(t_game *g, t_player *player, t_axis new_pos);

// TODO: Implement direction
bool	init_player(t_game *game)
{
	if (!set_player(game, &game->player))
		return (false);
	return (true);
}

static bool	set_player(t_game *game, t_player *player)
{
	t_axis	pos;
	char		**matrix;
	int			y;
	int			x;

	matrix = game->data.map.matrix;
	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x])
		{
			if (is_player(matrix[y][x]))
			{
				pos.x = (float)x + 0.5f;
				pos.y = (float)y + 0.5f;
				if (!update_player(game, player, pos))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}


bool	is_player(char player)
{
	int		i;
	char	*dir_set;

	dir_set = DIR_SET;
	i = 0;
	while (dir_set[i])
	{
		if (player == dir_set[i])
			return (true);
		i++;
	}
	return (false);
}

static bool	update_player(t_game *g, t_player *player, t_axis new_pos)
{
	char	*dir_set;
	int		y;
	int		x;

	if (player->pos.x != NPOS || player->pos.y != NPOS
		|| (player->dir.x != 0 || player->dir.y != 0))
	{
		display_error_message(MULTI_USER, false);
		g->error_flag = true;
		return (false);
	}
	update_pos(&player->pos, new_pos, &x, &y);
	dir_set = DIR_SET;
	if (dir_set[NORTH] == g->data.map.matrix[y][x])
		update_dir(NORTH, &player->dir);
	else if (dir_set[SOUTH] == g->data.map.matrix[y][x])
		update_dir(SOUTH, &player->dir);
	else if (dir_set[WEST] == g->data.map.matrix[y][x])
		update_dir(WEST, &player->dir);
	else
		update_dir(EAST, &player->dir);
	return (true);
}

static void	update_dir(t_directions dir, t_axis *dir_vector)
{
	if (dir == NORTH)
	{
		dir_vector->x = 0;
		dir_vector->y = -1;
	}
	else if (dir == SOUTH)
	{
		dir_vector->x = 0;
		dir_vector->y = 1;
	}
	else if (dir == WEST)
	{
		dir_vector->x = -1;
		dir_vector->y = 0;
	}
	else
	{
		dir_vector->x = 1;
		dir_vector->y = 0;
	}
}

static void	update_pos(t_axis *pos, t_axis new_pos, int *x, int *y)
{
	pos->x = new_pos.x;
	pos->y = new_pos.y;
	*x = (int)new_pos.x;
	*y = (int)new_pos.y;
}
