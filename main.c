#include "rush02.h"

int	main(int argc, char **argv)
{
	const char	*dict_path;
	const char	*input;
	char			*number;
	t_dict			dict;

	if (argc != 2 && argc != 3)
		return (ft_putstr_fd("Error\n", 2), 1);
	dict_path = "numbers.dict";
	input = argv[1];
	if (argc == 3)
	{
		dict_path = argv[1];
		input = argv[2];
	}
	if (!is_digit_string(input))
		return (ft_putstr_fd("Error\n", 2), 1);
	number = normalize_number(input);
	if (!number)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (!dict_load(dict_path, &dict))
		return (free(number), ft_putstr_fd("Dict Error\n", 2), 1);
	if (!print_number(&dict, number))
	{
		dict_free(&dict);
		free(number);
		return (ft_putstr_fd("Dict Error\n", 2), 1);
	}
	dict_free(&dict);
	free(number);
	return (0);
}
