#include "rush02.h"

static char	*grow_buffer(char *old, int used, int new_cap)
{
	char	*new_buf;
	int		i;

	new_buf = malloc(new_cap * sizeof(char));
	if (!new_buf)
		return (NULL);
	i = 0;
	while (i < used)
	{
		new_buf[i] = old[i];
		i++;
	}
	free(old);
	return (new_buf);
}

static char	*read_file(const char *path)
{
	int		fd;
	int		cap;
	int		used;
	int		r;
	char	*buf;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cap = 1024;
	used = 0;
	buf = malloc(cap * sizeof(char));
	if (!buf)
		return (close(fd), NULL);
	while (1)
	{
		if (used + 512 + 1 > cap)
		{
			cap *= 2;
			tmp = grow_buffer(buf, used, cap);
			if (!tmp)
				return (free(buf), close(fd), NULL);
			buf = tmp;
		}
		r = read(fd, buf + used, 512);
		if (r < 0)
			return (free(buf), close(fd), NULL);
		if (r == 0)
			break ;
		used += r;
	}
	close(fd);
	buf[used] = '\0';
	return (buf);
}

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	count_lines(const char *s)
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

static char	*copy_normalized_key(const char *s, int start, int end)
{
	while (start + 1 < end && s[start] == '0')
		start++;
	return (ft_strdup_range(s, start, end));
}

static int	add_entry(t_dict *dict, char *key, char *value)
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
	dict->items[dict->count].value = value;
	dict->count++;
	return (1);
}

static int	parse_line(const char *s, int start, int end, t_dict *dict)
{
	int	key_start;
	int	key_end;
	int	value_start;
	int	value_end;
	int	i;
	char	*key;
	char	*value;

	i = start;
	while (i < end && is_space(s[i]))
		i++;
	if (i == end)
		return (1);
	key_start = i;
	while (i < end && s[i] >= '0' && s[i] <= '9')
		i++;
	key_end = i;
	if (key_start == key_end)
		return (0);
	while (i < end && is_space(s[i]))
		i++;
	if (i >= end || s[i++] != ':')
		return (0);
	while (i < end && is_space(s[i]))
		i++;
	value_start = i;
	value_end = end;
	while (value_end > value_start && is_space(s[value_end - 1]))
		value_end--;
	if (value_start == value_end)
		return (0);
	i = value_start;
	while (i < value_end)
	{
		if ((unsigned char)s[i] < 32 || (unsigned char)s[i] > 126)
			return (0);
		i++;
	}
	key = copy_normalized_key(s, key_start, key_end);
	value = ft_strdup_range(s, value_start, value_end);
	if (!key || !value)
		return (free(key), free(value), 0);
	return (add_entry(dict, key, value));
}

int	dict_load(const char *path, t_dict *dict)
{
	char	*file;
	int		i;
	int		start;
	int		capacity;

	dict->items = NULL;
	dict->count = 0;
	file = read_file(path);
	if (!file)
		return (0);
	capacity = count_lines(file);
	dict->items = malloc(capacity * sizeof(t_entry));
	if (!dict->items)
		return (free(file), 0);
	i = 0;
	start = 0;
	while (1)
	{
		if (file[i] == '\n' || file[i] == '\0')
		{
			if (!parse_line(file, start, i, dict))
				return (free(file), dict_free(dict), 0);
			if (file[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	free(file);
	return (dict->count > 0);
}

void	dict_free(t_dict *dict)
{
	int	i;

	i = 0;
	while (i < dict->count)
	{
		free(dict->items[i].key);
		free(dict->items[i].value);
		i++;
	}
	free(dict->items);
	dict->items = NULL;
	dict->count = 0;
}

char	*dict_get(t_dict *dict, const char *key)
{
	int	i;

	i = 0;
	while (i < dict->count)
	{
		if (ft_strcmp(dict->items[i].key, key) == 0)
			return (dict->items[i].value);
		i++;
	}
	return (NULL);
}
