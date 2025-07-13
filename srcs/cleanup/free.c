#include "game.h"

void	free_tab(char **state)
{
	int	i;

	if (!state)
		return ;
	i = 0;
	while (state[i])
	{
		free(state[i]);
		i++;
	}
	free(state);
}
