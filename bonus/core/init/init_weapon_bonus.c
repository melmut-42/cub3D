#include "game.h"

void	weapon_ctor(t_weapon *weapon)
{
	weapon->weapon_img = NULL;
	weapon->frame_count = 0;
	weapon->jump_frame = 0;
	weapon->shake_offset_x = 0;
	weapon->shake_offset_y = 0;
	weapon->shake_direction_x = 1;
	weapon->shake_direction_y = 1;
	weapon->weapon_base_y = 0;
	weapon->load_attempted = false;
}
