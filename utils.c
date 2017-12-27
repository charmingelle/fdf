#include "header.h"

void				ft_swap(void **a, void **b)
{
	void *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

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
	return (c - '0');
}

unsigned int		ft_atoi_hex_color(char *s)
{
	unsigned int	result;
	int				i;

	result = 0;
	i = 2;
	while (i < 8)
		result = result * 16 + hex_to_digit(s[i++]);
	return (result);
}
