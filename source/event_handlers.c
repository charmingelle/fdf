/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:49:52 by grevenko          #+#    #+#             */
/*   Updated: 2017/12/29 15:02:37 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	mouse_handle(int key, int x, int y, t_env *env)
{
	int	scroll_limit;

	x = 0;
	y = 0;
	scroll_limit = fmax(env->wwidth, env->wheight);
	if (key == 4)
	{
		env->seglen < scroll_limit ? env->seglen += 1 : 0;
		draw(env);
	}
	else if (key == 5)
	{
		env->seglen > 1 ? env->seglen -= 1 : 0;
		draw(env);
	}
	return (0);
}

int	handle_key_press(int keycode, t_env *env)
{
	int	change_flag;
	int shift;

	change_flag = 0;
	shift = env->seglen / 4;
	keycode == ESC ? exit(0) : 0;
	keycode == A && ++change_flag ? (env->ang_y = (env->ang_y + 5) % 360) : 0;
	keycode == D && ++change_flag ? (env->ang_y = (env->ang_y - 5) % 360) : 0;
	keycode == W && ++change_flag ? (env->ang_x = (env->ang_x - 5) % 360) : 0;
	keycode == S && ++change_flag ? (env->ang_x = (env->ang_x + 5) % 360) : 0;
	keycode == Q && ++change_flag ? (env->ang_z = (env->ang_z + 5) % 360) : 0;
	keycode == E && ++change_flag ? (env->ang_z = (env->ang_z - 5) % 360) : 0;
	keycode == ARROW_LEFT && ++change_flag ? (env->shift_x -= shift) : 0;
	keycode == ARROW_RIGHT && ++change_flag ? (env->shift_x += shift) : 0;
	keycode == ARROW_UP && ++change_flag ? (env->shift_y -= shift) : 0;
	keycode == ARROW_DOWN && ++change_flag ? (env->shift_y += shift) : 0;
	change_flag ? draw(env) : 0;
	return (0);
}
