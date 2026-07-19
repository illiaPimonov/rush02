#include "rush02.h"

int	print_key(t_output *out, const char *key)
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

int	print_group(t_output *out, char group[3])
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

int	group_is_zero(char group[3])
{
	return (group[0] == '0'
		&& group[1] == '0'
		&& group[2] == '0');
}
