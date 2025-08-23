#include "game.h"
#include "bonus.h"

bool	init_weapon(t_game *game)
{
	t_weapon	*weapon;

	weapon = ft_calloc(1, sizeof(t_weapon));
	if (!weapon)
	{
		display_error_message(ERR_GAME, true);
		return (false);
	}
	game->weapon = weapon;
	weapon_ctor(weapon);
	if (!weapon->weapon_img)
	{
		weapon->weapon_img = xpm_to_img(game->mlx->mlx_ptr,
				WEAPON_TEXT);
		if (!weapon->weapon_img)
		{
			display_error_message("Could not load weapon texture!", true);
			return (false);
		}
	}
	return (true);
}
