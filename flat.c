#include "header.h"

t_flat  *get_flat(t_point *a, t_point *b, t_point *c, t_point *d)
{
   t_flat  *flat;
  
   flat = (t_flat *)malloc(sizeof(t_flat));
   flat->a = a;
   flat->b = b;
   flat->c = c;
   flat->d = d;
   flat->next = NULL;
   return (flat);
}

void    add_flat(t_flat **flats, t_flat *new)
{
    if (*flats == NULL)
        *flats = new;
    else
    {
        new->next = *flats;
        *flats = new;
    }  
}
