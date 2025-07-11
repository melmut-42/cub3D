#include "game.h"

// * Display error messages for necessary cases
void	display_error_message(const char *msg, bool is_perror)
{
	ft_putendl_fd(ERROR, STDERR_FILENO);
	ft_putendl_fd(BAR, STDERR_FILENO);
	if (is_perror)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	ft_putendl_fd(BAR, STDERR_FILENO);
}
