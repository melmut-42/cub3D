#include "game.h"

// * Display error messages for necessary cases
void	display_error_message(char *msg)
{
	if (msg)
	{
		ft_putendl_fd("Error", STDERR_FILENO);	// ? Use macro maybe
		ft_putendl_fd("----------------------", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		ft_putendl_fd("----------------------", STDERR_FILENO);
	}
}
