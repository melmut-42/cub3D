#include "game.h"

/**
 * @brief Initializes the weapon system for the game.
 *
 * @details
 * - Allocates memory for a new weapon instance using ft_calloc().
 * - Assigns the allocated weapon to the game structure.
 * - Calls weapon_ctor() to set default values.
 * - Loads the weapon texture from WEAPON_PATH if not already present.
 * - Displays an error and returns false on allocation or texture load failure.
 *
 * @param game (t_game *): Pointer to the main game structure.
 *
 * @return (bool): true if initialization is successful, false on failure.
 */
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
				WEAPON_PATH);
		if (!weapon->weapon_img)
		{
			display_error_message("Could not load weapon texture!", true);
			return (false);
		}
	}
	return (true);
}
