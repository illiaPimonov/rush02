#include "rush02.h"

typedef struct s_output
{
	t_dict	*dict;
	int		first;
}	t_output;

static int	print_key(t_output *out, const char *key)
{
	char	*value;

	value = dict_get(out->dict, key);
	if (!value)
		return (0);
	if (!out->first)
		write(1, " ", 1);
	ft_putstr_fd(value, 1);
	out->first = 0;
	return (1);
}

static int	print_digit(t_output *out, char digit)
{
	char	key[2];

	key[0] = digit;
	key[1] = '\0';
	return (print_key(out, key));
}

static int	print_under_100(t_output *out, char tens, char units)
{
	char	key[3];

	if (tens == '0')
	{
		if (units == '0')
			return (1);
		return (print_digit(out, units));
	}
	key[0] = tens;
	key[1] = units;
	key[2] = '\0';
	if (tens == '1')
		return (print_key(out, key));
	key[1] = '0';
	if (!print_key(out, key))
		return (0);
	if (units != '0' && !print_digit(out, units))
		return (0);
	return (1);
}

static int	print_group(t_output *out, char group[3])
{
	if (group[0] != '0')
	{
		if (!print_digit(out, group[0]))
			return (0);
		if (!print_key(out, "100"))
			return (0);
	}
	return (print_under_100(out, group[1], group[2]));
}

static int	group_is_zero(char group[3])
{
	return (group[0] == '0'
		&& group[1] == '0'
		&& group[2] == '0');
}

static void	copy_group(const char *number, int start,
		int count, char group[3])
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
	{
		key[i] = '0';
		i++;
	}
	key[i] = '\0';
	return (key);
}

static int	print_scale(t_output *out, int remaining_groups)
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

int	print_number(t_dict *dict, const char *number)
{
	t_output	out;
	char		*exact;
	int			len;
	int			first_group_size;
	int			group_count;
	int			start;
	int			group_number;
	int			remaining_groups;
	char		group[3];

	out.dict = dict;
	out.first = 1;
	exact = dict_get(dict, number);
	if (exact)
	{
		ft_putstr_fd(exact, 1);
		write(1, "\n", 1);
		return (1);
	}
	len = ft_strlen(number);
	first_group_size = len % 3;
	if (first_group_size == 0)
		first_group_size = 3;
	group_count = (len + 2) / 3;
	start = 0;
	group_number = 0;
	while (group_number < group_count)
	{
		if (group_number == 0)
			copy_group(number, start, first_group_size, group);
		else
			copy_group(number, start, 3, group);
		if (!group_is_zero(group))
		{
			if (!print_group(&out, group))
				return (0);
			remaining_groups = group_count - group_number - 1;
			if (remaining_groups > 0
				&& !print_scale(&out, remaining_groups))
				return (0);
		}
		if (group_number == 0)
			start += first_group_size;
		else
			start += 3;
		group_number++;
	}
	write(1, "\n", 1);
	return (1);
}