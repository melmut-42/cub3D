#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd);
void	clear_get_next_line(int fd);

int		ft_is_newline_char(const char *s);
char	*ft_update_repo(char *total_line, char *repo);
int		ft_set_d(char **data);
char	*ft_free_and_update_repo(char **old, char *new);
char	*ft_free_and_clean(char **data);
char	*ft_get_the_line(char *data);

#endif
