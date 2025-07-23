#include "game.h"

static void	update_rot_angles(t_player *player, int delta_x, int delta_y);

// * Handles mouse events within the game window
int handle_mouse(int x, int y, t_game *game)
{
    static int  cur_x = NPOS;
    static int  cur_y = NPOS;
    int dx;
    int dy;

    // Update mouse position for the first time
    if (cur_x == NPOS || cur_y == NPOS)
    {
       cur_x = x;
       cur_y = y;
       return (0);
    }

    dx = x - cur_x;
    dy = y - cur_y;

    // update dirs and angles by basing on rotation angles
    update_rot_angles(&game->player, dx, dy);

    cur_x = x;
    cur_y = y;

    return (0);
}

// * Update rotations and angles by using particular restrictions base on deltas
static void	update_rot_angles(t_player *player, int delta_x, int delta_y)
{
	if (delta_y >  MAX_VERTICAL_DELTA)
		delta_y =  MAX_VERTICAL_DELTA;

    if (delta_y < -MAX_VERTICAL_DELTA)
		delta_y = -MAX_VERTICAL_DELTA;

	player->rot.x = delta_x * player->sens.x;
    player->pitch_angle -= delta_y * player->sens.y;

	if (player->pitch_angle >  MAX_PITCH)
		player->pitch_angle =  MAX_PITCH;

    if (player->pitch_angle <  MIN_PITCH)
		player->pitch_angle =  MIN_PITCH;
}
