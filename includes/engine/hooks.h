#ifndef HOOKS_H
# define HOOKS_H

# include "../core/structures.h"

int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);
int		handle_mouse(int x, int y, t_game *game);
void	init_hooks(t_game *game);

#endif
