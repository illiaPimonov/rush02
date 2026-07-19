#include "rush02.h"

void	copy_group(const char *number, int start, int count, char group[3])
{
	int	i;
	int	offset;

	group[0] = '0';
	group[1] = '0';
	group[2] = '0';
	offset = 3 - count;
	i = 0;
	while (i < count)
	{
		group[offset + i] = number[start + i];
		i++;
	}
}

static char	*make_scale_key(int zero_count)
{
	char	*key;
	int		i;

	key = malloc(sizeof(char) * (zero_count + 2));
	if (!key)
		return (NULL);
	key[0] = '1';
	i = 1;
	while (i <= zero_count)
		key[i++] = '0';
	key[i] = '\0';
	return (key);
}

int	print_scale(t_output *out, int remaining_groups)
{
	char	*key;
	int		ok;

	key = make_scale_key(remaining_groups * 3);
	if (!key)
		return (0);
	ok = print_key(out, key);
	free(key);
	return (ok);
}
