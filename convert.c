#include "rush02.h"

static int	is_scale_number(const char *number)
{
	int	i;

	if (number[0] != '1' || number[1] != '0' || number[2] != '0')
		return (0);
	i = 1;
	while (number[i] == '0')
		i++;
	return (number[i] == '\0');
}

static void	init_convert(t_convert *state, const char *number)
{
	state->len = ft_strlen(number);
	state->first_size = state->len % 3;
	if (state->first_size == 0)
		state->first_size = 3;
	state->group_count = (state->len + 2) / 3;
	state->start = 0;
	state->group_index = 0;
}

static int	process_group(t_output *out, t_convert *state, char group[3])
{
	int	remaining;

	if (group_is_zero(group))
		return (1);
	if (!print_group(out, group))
		return (0);
	remaining = state->group_count - state->group_index - 1;
	if (remaining > 0 && !print_scale(out, remaining))
		return (0);
	return (1);
}

static int	print_groups(t_output *out, const char *number)
{
	t_convert	state;
	char		group[3];
	int			count;

	init_convert(&state, number);
	while (state.group_index < state.group_count)
	{
		count = 3;
		if (state.group_index == 0)
			count = state.first_size;
		copy_group(number, state.start, count, group);
		if (!process_group(out, &state, group))
			return (0);
		state.start += count;
		state.group_index++;
	}
	return (1);
}

int	print_number(t_dict *dict, const char *number)
{
	t_output	out;
	char		*exact;

	exact = NULL;
	if (!is_scale_number(number))
		exact = dict_get(dict, number);
	if (exact)
	{
		ft_putstr_fd(exact, 1);
		write(1, "\n", 1);
		return (1);
	}
	out.dict = dict;
	out.first = 1;
	if (!print_groups(&out, number))
		return (0);
	write(1, "\n", 1);
	return (1);
}
