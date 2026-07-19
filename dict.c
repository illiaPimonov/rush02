#include "rush02.h"

static int	parse_file(char *file, t_dict *dict)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (1)
	{
		if (file[i] == '\n' || file[i] == '\0')
		{
			if (!parse_line(file, start, i, dict))
				return (0);
			if (file[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	return (1);
}

int	dict_load(const char *path, t_dict *dict)
{
	char	*file;
	int		capacity;

	dict->items = NULL;
	dict->count = 0;
	file = read_file(path);
	if (!file)
		return (0);
	capacity = count_lines(file);
	dict->items = malloc(sizeof(t_entry) * capacity);
	if (!dict->items)
		return (free(file), 0);
	if (!parse_file(file, dict))
		return (free(file), dict_free(dict), 0);
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
