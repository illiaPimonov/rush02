#include "rush02.h"

static char	*grow_buffer(char *old, int used, int capacity)
{
	char	*new_buffer;
	int		i;

	new_buffer = malloc(sizeof(char) * capacity);
	if (!new_buffer)
		return (NULL);
	i = 0;
	while (i < used)
	{
		new_buffer[i] = old[i];
		i++;
	}
	free(old);
	return (new_buffer);
}

static int	expand_reader(t_reader *reader)
{
	char	*new_buffer;

	reader->capacity *= 2;
	new_buffer = grow_buffer(reader->buffer, reader->used, reader->capacity);
	if (!new_buffer)
		return (0);
	reader->buffer = new_buffer;
	return (1);
}

static int	read_content(t_reader *reader)
{
	int	bytes;

	while (1)
	{
		if (reader->used + 513 > reader->capacity && !expand_reader(reader))
			return (0);
		bytes = read(reader->fd, reader->buffer + reader->used, 512);
		if (bytes < 0)
			return (0);
		if (bytes == 0)
			break ;
		reader->used += bytes;
	}
	reader->buffer[reader->used] = '\0';
	return (1);
}

char	*read_file(const char *path)
{
	t_reader	reader;

	reader.fd = open(path, O_RDONLY);
	if (reader.fd < 0)
		return (NULL);
	reader.capacity = 1024;
	reader.used = 0;
	reader.buffer = malloc(sizeof(char) * reader.capacity);
	if (!reader.buffer)
		return (close(reader.fd), NULL);
	if (!read_content(&reader))
		return (free(reader.buffer), close(reader.fd), NULL);
	close(reader.fd);
	return (reader.buffer);
}
