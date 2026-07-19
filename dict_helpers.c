#include "rush02.h"

static char	*normalized_key(const char *s, int start, int end)
{
	while (start + 1 < end && s[start] == '0')
		start++;
	return (ft_strdup_range(s, start, end));
}

int	count_lines(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	add_entry(t_dict *dict, char *key, char *value)
{
	int	i;

	i = 0;
	while (i < dict->count)
	{
		if (ft_strcmp(dict->items[i].key, key) == 0)
		{
			free(dict->items[i].value);
			dict->items[i].value = value;
			free(key);
			return (1);
		}
		i++;
	}
	dict->items[dict->count].key = key;
	dict->items[dict->count++].value = value;
	return (1);
}

int	make_entry(const char *s, t_bounds *bounds, t_dict *dict)
{
	char	*key;
	char	*value;

	key = normalized_key(s, bounds->key_start, bounds->key_end);
	value = ft_strdup_range(s, bounds->value_start, bounds->value_end);
	if (!key || !value)
		return (free(key), free(value), 0);
	return (add_entry(dict, key, value));
}
