#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include "../libs/libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

# define NULL_PATH "/dev/null"

char	*get_next_line(int fd);
void	clear_get_next_line(void);


int		ft_is_newline_char(const char *s);
char	*ft_update_repo(char *total_line, char *repo);
int		ft_set_d(char **data);
char	*ft_free_and_clean(char **data);
char	*ft_free_and_update_repo(char **old, char *new);

#endif
