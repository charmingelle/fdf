/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:07:16 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/01 18:50:22 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFF_SIZE 100

typedef struct	s_fdlist {
	int				fd;
	char			*text;
	struct s_fdlist	*next;
}				t_fdlist;

int				get_next_line(const int fd, char **line);

#endif
