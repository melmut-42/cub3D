#include "game.h"

static void	yaw(t_game *game, t_player *player);

void	update_player_movement(t_game *g, t_player *p)
{
	t_axis	strafe;

	strafe.x = -p->dir.y;
	strafe.y = p->dir.x;
	if (p->movement[W])
		attempt_move(g, &p->pos, p->dir.x * p->mov_speed,
			p->dir.y * p->mov_speed);
	if (p->movement[S])
		attempt_move(g, &p->pos, -p->dir.x * p->mov_speed,
			-p->dir.y * p->mov_speed);
	if (p->movement[D])
		attempt_move(g, &p->pos, strafe.x * p->mov_speed,
			strafe.y * p->mov_speed);
	if (p->movement[A])
	{
		attempt_move(g, &p->pos, -strafe.x * p->mov_speed,
			-strafe.y * p->mov_speed);
	}
	yaw(g, p);
}

static void	yaw(t_game *game, t_player *player)
{
	double	angle;

	if (player->rot.x)
	{
		angle = player->rot.x * player->sens.x;
		rotate_vector(&game->data, &player->dir, angle);
		rotate_vector(&game->data, &player->plane, angle);
		player->rot.x = 0;
	}
}
