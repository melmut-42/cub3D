#include "game.h"

/**
 * @brief Displays a formatted error message to standard error.
 *
 * @details
 * - If is_perror is true, uses perror() to display the system error message.
 * - Otherwise, prints the provided message string if not NULL.
 *
 * @param msg (const char *): The error message or context string.
 * @param is_perror (bool): Whether to use perror() for system error output.
 *
 * @return void
 */
void	display_error_message(const char *msg, bool is_perror)
{
	ft_putendl_fd(ERROR, STDERR_FILENO);
	ft_putendl_fd(BAR, STDERR_FILENO);
	if (is_perror)
		perror(msg);
	else if (msg)
		ft_putendl_fd((char *)msg, STDERR_FILENO);
	ft_putendl_fd(BAR, STDERR_FILENO);
}
