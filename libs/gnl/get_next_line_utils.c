#include "get_next_line.h"

char	*ft_update_repo(char *total_line, char *repo)
{
	size_t	repo_len;
	size_t	line_len;

	repo_len = ft_strlen(repo);
	line_len = ft_strlen(total_line);
	return (ft_substr(repo, line_len, repo_len - line_len));
}

int	ft_is_newline_char(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	clear_get_next_line(int fd)
{
	char	*line;

	if (fd < 0)
	{
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}
