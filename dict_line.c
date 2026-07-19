#include "rush02.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	parse_key(const char *s, int *index, int end, t_bounds *bounds)
{
	while (*index < end && is_space(s[*index]))
		(*index)++;
	if (*index == end)
		return (2);
	bounds->key_start = *index;
	while (*index < end && s[*index] >= '0' && s[*index] <= '9')
		(*index)++;
	bounds->key_end = *index;
	if (bounds->key_start == bounds->key_end)
		return (0);
	while (*index < end && is_space(s[*index]))
		(*index)++;
	if (*index >= end || s[(*index)++] != ':')
		return (0);
	return (1);
}

static int	parse_value(const char *s, int index, int end, t_bounds *bounds)
{
	while (index < end && is_space(s[index]))
		index++;
	bounds->value_start = index;
	bounds->value_end = end;
	while (bounds->value_end > index
		&& is_space(s[bounds->value_end - 1]))
		bounds->value_end--;
	if (bounds->value_start == bounds->value_end)
		return (0);
	while (index < bounds->value_end)
	{
		if ((unsigned char)s[index] < 32 || (unsigned char)s[index] > 126)
			return (0);
		index++;
	}
	return (1);
}

int	parse_line(const char *s, int start, int end, t_dict *dict)
{
	t_bounds	bounds;
	int			index;
	int			key_status;

	index = start;
	key_status = parse_key(s, &index, end, &bounds);
	if (key_status == 2)
		return (1);
	if (!key_status || !parse_value(s, index, end, &bounds))
		return (0);
	return (make_entry(s, &bounds, dict));
}
