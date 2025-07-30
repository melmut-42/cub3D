#include "game.h"

// * Display error messages for necessary cases
void	display_error_message(const char *msg, bool is_perror)
{
	// Print general error header
	ft_putendl_fd(ERROR, STDERR_FILENO);

	// Print the error msg
	ft_putendl_fd(BAR, STDERR_FILENO);

	// Print the specific error msg if provided
	if (is_perror)
		perror(msg);
	
	// Otherwise print the custom msg directly
	else if (msg)
		ft_putendl_fd((char *)msg, STDERR_FILENO);

	// Print the footer / closing bar
	ft_putendl_fd(BAR, STDERR_FILENO);
}
