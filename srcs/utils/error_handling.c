#include "game.h"

// TODO: consider returning a different value
void	handle_error(t_err_code err_code, bool exit_program)
{
	if (err_code == MALLOC_ERR)
		ft_putendl_fd("Memory allocation error", STDERR_FILENO);
	else if (err_code == RENDER_ERR)
		ft_putendl_fd("Rendering error", STDERR_FILENO);

	if (exit_program)
		exit(EXIT_FAILURE);
}
