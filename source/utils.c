#include "header.h"

double				degree_to_rad(int degree)
{
	return (((double)degree * M_PI) / 180.0);
}

static unsigned int	hex_to_digit(char c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a');
	if (c >= 'A' && c <= 'F')
		return (c - 'A');
	if (c >= '0' && c <= '9')
		return (c - '0');
	exit(show_invalid_color_error());
}

unsigned int		ft_atoi_hex_color(char *s)
{
	unsigned int	result;
	int				i;

	if ((ft_strlen(s) != 8) || (s[0] != '0') || (s[1] != 'x'))
		exit(show_invalid_color_error());
	result = 0;
	i = 2;
	while (i < 8)
		result = result * 16 + hex_to_digit(s[i++]);
	return (result);
}
