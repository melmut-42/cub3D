#include "game.h"

static void	pitch(t_player *player);
static void	yaw(t_game *game, t_player *player);

// * Handles player movement and rotation
void update_player_movement(t_game *g, t_player *p, t_map *map)
{
    t_axis strafe;

    strafe.x = -p->dir.y;
    strafe.y =  p->dir.x;

    if (p->mov_up)
        attempt_move(map, &p->pos, p->dir.x * p->mov_speed,  p->dir.y * p->mov_speed);
    if (p->mov_down)
        attempt_move(map, &p->pos, -p->dir.x * p->mov_speed, -p->dir.y * p->mov_speed);
    if (p->mov_right)
        attempt_move(map, &p->pos, strafe.x * p->mov_speed,  strafe.y * p->mov_speed);
    if (p->mov_left)
	{
		attempt_move(map, &p->pos, -strafe.x * p->mov_speed, -strafe.y * p->mov_speed);
	}

	// execute yaw & pitch
	pitch(p);
	yaw(g, p);
}

// Updates player for horizontal movement 
static void	yaw(t_game *game, t_player *player)
{
    double angle;

    if (player->rot.x)
    {
        angle = player->rot.x * player->sens.x;
        rotate_vector(&game->data, &player->dir, angle);
        rotate_vector(&game->data, &player->plane, angle);
        player->rot.x = 0;
    }
}

// Updates player for horizontal movement
static void	pitch(t_player *player)
{
    if (player->rot.y)
    {
        player->pitch_angle += player->rot.y * player->sens.y;
        player->rot.y = 0;
    }
}


void update_player_vertical(t_player *p, double dt)
{
    if (p->vertical.in_air)
    {
        p->vertical.vertical_vel -= GRAVITY * dt;
        p->vertical.vertical_pos += p->vertical.vertical_vel * dt;
        if (p->vertical.vertical_pos <= 0.0)
        {
            p->vertical.vertical_pos = 0.0;
            p->vertical.vertical_vel = 0.0;
            p->vertical.in_air = false;
        }
    }
    // convert world-units to pixel-offset for camera
    p->vertical.jump_offset = p->vertical.vertical_pos * JUMP_SCALE;
}
