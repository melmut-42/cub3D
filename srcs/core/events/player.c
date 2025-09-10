#include "game.h"

static void	pitch(t_player *player);
static void	yaw(t_game *game, t_player *player);

/**
 * @brief Updates player movement and orientation.
 *
 * @details
 * - Handles forward/backward movement (W, S).
 * - Handles strafing (A, D).
 * - Updates pitch (looking up/down).
 * - Updates yaw (looking left/right).
 *
 * @param g (t_game *): Pointer to the game structure.
 * @param p (t_player *): Pointer to the player structure.
 * 
 * @return void
 */
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

/**
 * @brief Simulates jump physics for the player.
 *
 * @details
 * - Applies gravity to vertical velocity.
 * - Updates vertical position over time.
 * - Stops jump when the player lands back on the ground.
 * - Updates jump offset used for rendering (jump_off).
 *
 * @param p (t_player *): Pointer to the player structure.
 * @param dt (double): Delta time (in seconds).
 * 
 * @return void
 */
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

/**
 * @brief Smoothly transitions the player from crouching to standing.
 *
 * @details
 * - Decreases crouch offset towards crouch_target.
 * - Ensures the offset never goes below the target.
 *
 * @param p (t_player *): Pointer to the player structure.
 * @param dt (double): Delta time (in seconds).
 * 
 * @return void
 */
void	stand_up(t_player *p, double dt)
{
	if (p->vertical.crouch_off > p->vertical.crouch_target)
	{
		p->vertical.crouch_off -= CROUCH_OUT_SPEED * dt;
		if (p->vertical.crouch_off < p->vertical.crouch_target)
			p->vertical.crouch_off = p->vertical.crouch_target;
	}
}

/**
 * @brief Applies yaw (horizontal rotation) to the player.
 *
 * @details
 * - If horizontal rotation input (rot.x) exists, calculates the rotation angle
 *   using sensitivity.
 * - Rotates both the direction vector and the camera plane vector around the Z-axis.
 * - Resets rot.x after applying to avoid repeated rotation in the next frame.
 *
 * @param game (t_game *): Pointer to the main game structure.
 * @param player (t_player *): Pointer to the player structure.
 * 
 * @return void
 */
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

/**
 * @brief Applies pitch (vertical rotation) to the player.
 *
 * @details
 * - If vertical rotation input (rot.y) exists, updates the pitch angle
 *   using sensitivity.
 * - Resets rot.y after applying to avoid repeated rotation in the next frame.
 *
 * @param player (t_player *): Pointer to the player structure.
 * 
 * @return void
 */
static void	pitch(t_player *player)
{
	if (player->rot.y)
	{
		player->pitch_angle += player->rot.y * player->sens.y;
		player->rot.y = 0;
	}
}
