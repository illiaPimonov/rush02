#include "rush02.h"

static int	select_args(int argc, char **argv, const char **path,
		const char **input)
{
	if (argc != 2 && argc != 3)
		return (0);
	*path = "numbers.dict";
	*input = argv[1];
	if (argc == 3)
	{
		*path = argv[1];
		*input = argv[2];
	}
	return (1);
}

static int	run_program(const char *path, char *number)
{
	t_dict	dict;
	int		ok;

	if (!dict_load(path, &dict))
		return (ft_putstr_fd("Dict Error\n", 2), 1);
	ok = print_number(&dict, number);
	dict_free(&dict);
	if (!ok)
		return (ft_putstr_fd("Dict Error\n", 2), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	const char	*path;
	const char	*input;
	char			*number;
	int			status;

	if (!select_args(argc, argv, &path, &input) || !is_digit_string(input))
		return (ft_putstr_fd("Error\n", 2), 1);
	number = normalize_number(input);
	if (!number)
		return (ft_putstr_fd("Error\n", 2), 1);
	status = run_program(path, number);
	free(number);
	return (status);
}
