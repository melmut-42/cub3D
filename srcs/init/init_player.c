#include "game.h"

static void	update_dir(t_directions dir, t_player *p);
static void	update_pos(t_axis *pos, t_axis new_pos, int *x, int *y);
static bool	set_player(t_game *game, t_player *player);
static bool	update_player(t_game *g, t_player *player, t_axis new_pos);

bool	init_player(t_game *game)
{
	if (!set_player(game, &game->player))
		return (false);
	if (game->player.pos.x == NPOS || game->player.pos.y == NPOS)
	{
		display_error_message(PLAYER_NOT_EXIST_ERR, false);
		game->error_flag = true;
		return (false);
	}
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

	if (player->pos.x != NPOS && player->pos.y != NPOS)
	{
		display_error_message(MULTI_PLAYER, false);
		g->error_flag = true;
		return (false);
	}
	update_pos(&player->pos, new_pos, &x, &y);
	dir_set = DIR_SET;
	if (dir_set[NORTH] == g->data.map.matrix[y][x])
		update_dir(NORTH, player);
	else if (dir_set[SOUTH] == g->data.map.matrix[y][x])
		update_dir(SOUTH, player);
	else if (dir_set[WEST] == g->data.map.matrix[y][x])
		update_dir(WEST, player);
	else
		update_dir(EAST, player);
	return (true);
}

static void	update_dir(t_directions dir, t_player *p)
{
	p->dir.x = (dir == WEST) * -1 + (dir == EAST);
	p->dir.y = (dir == NORTH) * -1 + (dir == SOUTH);
	if (dir == NORTH)
	{
		p->plane.x = 0.66;
		p->plane.y = 0;
	}
	else if (dir == SOUTH)
	{
		p->plane.x = -0.66;
		p->plane.y = 0;
	}
	else if (dir == WEST)
	{
		p->plane.x = 0;
		p->plane.y = -0.66;
	}
	else if (dir == EAST)
	{
		p->plane.x = 0;
		p->plane.y = 0.66;
	}
}

static void	update_pos(t_axis *pos, t_axis new_pos, int *x, int *y)
{
	pos->x = new_pos.x;
	pos->y = new_pos.y;
	*x = (int)new_pos.x;
	*y = (int)new_pos.y;
}
