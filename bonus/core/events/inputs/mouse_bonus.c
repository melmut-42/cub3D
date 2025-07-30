#include "game.h"

static void	update_rot_angles(t_player *player, int delta_x, int delta_y);

// * Handles mouse events within the game window
int handle_mouse(int x, int y, t_game *game)
{
    static int last_x = MID_POINT_X;
    static int last_y = MID_POINT_Y;

    int dx = x - last_x;
    int dy = y - last_y;

    if (dx != 0 || dy != 0)
    {
        update_rot_angles(&game->player, dx, dy);
        mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->win_ptr, MID_POINT_X, MID_POINT_Y);
    }

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
