#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_entry
{
	char	*key;
	char	*value;
}t_entry;

typedef struct s_dict
{
	t_entry	*items;
	int		count;
}t_dict;

typedef struct s_output
{
	t_dict	*dict;
	int		first;
}t_output;

typedef struct s_reader
{
	int		fd;
	int		capacity;
	int		used;
	char	*buffer;
}t_reader;

typedef struct s_bounds
{
	int	key_start;
	int	key_end;
	int	value_start;
	int	value_end;
}t_bounds;

typedef struct s_convert
{
	int	len;
	int	first_size;
	int	group_count;
	int	start;
	int	group_index;
}t_convert;

int		ft_strlen(const char *s);
int		ft_strcmp(const char *a, const char *b);
char	*ft_strdup_range(const char *s, int start, int end);
void	ft_putstr_fd(const char *s, int fd);
int		is_digit_string(const char *s);
char	*normalize_number(const char *s);

char	*read_file(const char *path);
int		count_lines(const char *s);
int		parse_line(const char *s, int start, int end, t_dict *dict);
int		add_entry(t_dict *dict, char *key, char *value);
int		make_entry(const char *s, t_bounds *bounds, t_dict *dict);
int		dict_load(const char *path, t_dict *dict);
void	dict_free(t_dict *dict);
char	*dict_get(t_dict *dict, const char *key);

int		print_key(t_output *out, const char *key);
int		print_group(t_output *out, char group[3]);
int		group_is_zero(char group[3]);
void	copy_group(const char *number, int start, int count, char group[3]);
int		print_scale(t_output *out, int remaining_groups);
int		print_number(t_dict *dict, const char *number);

#endif
