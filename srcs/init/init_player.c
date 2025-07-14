#include "game.h"

static void	player_ctor(t_player *player);
static bool	set_player(t_game *game, t_player *player);
static bool	update_player_pos(t_game *g, t_player *player, t_position new_pos);

bool	init_player(t_game *game)
{
	player_ctor(&game->player);
	if (!set_player(game, &game->player))
		return (false);
	return (true);
}

static void	player_ctor(t_player *player)
{
	player->pos.x_axis = NPOS;
	player->pos.y_axis = NPOS;
	player->dir = NONE;
}

static bool	set_player(t_game *game, t_player *player)
{
	t_position	pos;
	char		**matrix;

	pos.y_axis = -1;
	matrix = game->data.map.matrix;
	while (matrix[++(pos.y_axis)])
	{
		pos.x_axis = -1;
		while (matrix[pos.y_axis][++(pos.x_axis)])
		{
			if (is_player(matrix[pos.y_axis][pos.x_axis]))
				if (!update_player_pos(game, player, pos))
					return (false);
		}
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

static bool	update_player_pos(t_game *g, t_player *player, t_position new_pos)
{
	int		i;
	char	*dir_set;

	if (player->pos.x_axis != NPOS || player->pos.y_axis != NPOS
		|| player->dir != NONE)
	{
		display_error_message(MULTI_USER, false);
		g->error_flag = true;
		return (false);
	}
	player->pos.x_axis = new_pos.x_axis;
	player->pos.y_axis = new_pos.y_axis;
	i = 0;
	dir_set = DIR_SET;
	if (dir_set[NORTH] == g->data.map.matrix[new_pos.y_axis][new_pos.x_axis])
		player->dir = NORTH;
	else if (dir_set[SOUTH] == g->data.map.matrix[new_pos.y_axis][new_pos.x_axis])
		player->dir = SOUTH;
	else if (dir_set[WEST] == g->data.map.matrix[new_pos.y_axis][new_pos.x_axis])
		player->dir = WEST;
	else
		player->dir = EAST;
	return (true);
}
