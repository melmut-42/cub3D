#include "game.h"

static void	pitch(t_player *player);
static void	yaw(t_game *game, t_player *player);

void	update_player_movement(t_game *g, t_player *p)
{
	t_axis	strafe;

	strafe.x = -p->dir.y;
	strafe.y = p->dir.x;
	if (p->movement[W])
		attempt_move(g, &p->pos,
			p->dir.x * p->mov_speed, p->dir.y * p->mov_speed);
	if (p->movement[S])
		attempt_move(g, &p->pos,
			-p->dir.x * p->mov_speed, -p->dir.y * p->mov_speed);
	if (p->movement[D])
		attempt_move(g, &p->pos,
			strafe.x * p->mov_speed, strafe.y * p->mov_speed);
	if (p->movement[A])
	{
		attempt_move(g, &p->pos,
			-strafe.x * p->mov_speed, -strafe.y * p->mov_speed);
	}
	pitch(p);
	yaw(g, p);
}

void	jump_event(t_player *p, double dt)
{
	if (p->vertical.in_air)
	{
		p->vertical.vertical_vel -= GRAVITY * dt;
		p->vertical.vertical_pos += p->vertical.vertical_vel * dt;
		if (p->vertical.vertical_pos <= 0.0)
		{
			p->vertical.vertical_pos = 0.0;
			p->vertical.vertical_vel = 0.0;
			p->mov_speed = INITIAL_SPEED;
			p->vertical.in_air = false;
		}
	}
	p->vertical.jump_off = p->vertical.vertical_pos * JUMP_SCALE;
}

void	stand_up(t_player *p, double dt)
{
	if (p->vertical.crouch_off > p->vertical.crouch_target)
	{
		p->vertical.crouch_off -= CROUCH_OUT_SPEED * dt;
		if (p->vertical.crouch_off < p->vertical.crouch_target)
			p->vertical.crouch_off = p->vertical.crouch_target;
	}
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

static void	pitch(t_player *player)
{
	if (player->rot.y)
	{
		player->pitch_angle += player->rot.y * player->sens.y;
		player->rot.y = 0;
	}
}
