#include "rush02.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

char	*ft_strdup_range(const char *s, int start, int end)
{
	char	*out;
	int		i;

	if (end < start)
		return (NULL);
	out = malloc(sizeof(char) * (end - start + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (start < end)
		out[i++] = s[start++];
	out[i] = '\0';
	return (out);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	is_digit_string(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
