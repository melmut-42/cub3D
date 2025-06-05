#include "get_next_line.h"

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

char	*ft_update_repo(char *total_line, char *repo)
{
	char	*new_repo;
	size_t	repo_len;
	size_t	line_len;

	repo_len = ft_strlen(repo);
	line_len = ft_strlen(total_line);
	new_repo = ft_substr(repo, line_len, repo_len - line_len);
	if (repo)
		free(repo);
	return (new_repo);
}

int	ft_set_d(char **data)
{
	if (!data)
		return (1);
	if (*data == NULL)
	{
		*data = (char *) malloc(sizeof(char));
		if (*data)
			**data = '\0';
		else
			return (1);
	}
	return (0);
}

char	*ft_free_and_update_repo(char **old, char *new)
{
	if (*old)
		free(*old);
	*old = new;
	return (new);
}

char	*ft_free_and_clean(char **data)
{
	if (*data)
	{
		free(*data);
		*data = NULL;
	}
	return (NULL);
}
