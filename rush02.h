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

int		ft_strlen(const char *s);
int		ft_strcmp(const char *a, const char *b);
char	*ft_strdup_range(const char *s, int start, int end);
void	ft_putstr_fd(const char *s, int fd);
int		is_digit_string(const char *s);
char	*normalize_number(const char *s);

int		dict_load(const char *path, t_dict *dict);
void	dict_free(t_dict *dict);
char	*dict_get(t_dict *dict, const char *key);

int		print_number(t_dict *dict, const char *number);

#endif
