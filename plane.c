#include "header.h"

t_plane	*create_plane(double visibility)
{
	t_plane *plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		exit(1);
	plane->visibility = visibility;
	plane->next = NULL;
	return (plane);
}

void	add_plane(t_plane **plane, double visibility)
{
	t_plane *new;

	new = create_plane(visibility);
	if (*plane == NULL)
		*plane = new;
	else
	{
		new->next = *plane;
		*plane = new;
	}
}

void	free_plane(t_plane **plane)
{
	t_plane *to_free;

	while (*plane)
	{
		to_free = *plane;
		plane = &((*plane)->next);
		free(to_free);
	}
}
