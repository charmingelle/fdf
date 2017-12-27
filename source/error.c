#include "header.h"

int	show_invalid_color_error(void)
{
	write(1, "The map contains an invalid color\n", 34);
	return (1);
}

int	show_invalid_size_error(void)
{
	write(1, "The lines of the map do not contain equal amounts of points\n", 60);
	return (1);
}

int	show_invalid_file_error(void)
{
	write(1, "No such file\n", 13);
	return (1);
}

int	show_malloc_error(void)
{
	write(1, "The memory cannot be allocated\n", 31);
	return (1);
}
