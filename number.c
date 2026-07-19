#include "rush02.h"

char	*normalize_number(const char *s)
{
	int	i;
	int	len;

	i = 0;
	while (s[i] == '0' && s[i + 1])
		i++;
	len = ft_strlen(s);
	return (ft_strdup_range(s, i, len));
}
