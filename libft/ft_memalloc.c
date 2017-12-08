/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 13:50:09 by grevenko          #+#    #+#             */
/*   Updated: 2017/11/07 12:00:00 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *p;
	void *p_start;

	p = malloc(size);
	if (p == 0)
		return (0);
	p_start = p;
	while (size-- > 0)
		*(unsigned char *)p++ = 0;
	return (p_start);
}
