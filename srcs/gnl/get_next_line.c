#include "get_next_line.h"
#include "fcntl.h"
#include "unistd.h"

static char	*ft_get_the_line(char *data);

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*repo = NULL;
	char		*total_line;
	int			bytes_read;

	if (fd < 0 || ft_set_d(&repo) || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 0;
	while (repo && !ft_is_newline_char(repo))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		ft_free_and_update_repo(&repo, ft_strjoin(repo, buffer));
	}
	if (!repo)
		return (ft_free_and_clean(&repo));
	if (bytes_read == -1 || repo[0] == '\0')
		return (ft_free_and_clean(&repo));
	total_line = ft_get_the_line(repo);
	if (!total_line)
		return (ft_free_and_clean(&repo));
	ft_free_and_update_repo(&repo, ft_update_repo(total_line, repo));
	return (total_line);
}
void	clear_get_next_line(void)
{
	int		fd;
	char	*value;

	fd = open(NULL_PATH, O_RDONLY);
	if (fd < 0)
		return;
	value = get_next_line(fd);
	while (value)
	{
		free(value);
		value = get_next_line(fd);
	}
}

static char	*ft_get_the_line(char *data)
{
	size_t	len;

	if (!data)
		return (NULL);
	len = 0;
	while (data[len] != '\0')
	{
		if (data[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	return (ft_substr(data, 0, len));
}
