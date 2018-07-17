/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 20:49:10 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/14 20:49:13 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** It is with the mlx_hook function that one creates custom hooks. funct can
** take any number/types of arguments.
**
** int	mlx_hook(t_win_list *win, int x_event, int x_mask, 
**		 int (*funct)(),void *param)
** {
**  win->hooks[x_event].hook = funct;
**  win->hooks[x_event].param = param;
**  win->hooks[x_event].mask = x_mask;
** }
*/

int		handle_mouse_press(int button, int x, int y, void *param)
{
	t_control		*ctrl;
	static int		no_render = 1;
	static t_point	prev_press = {-1, -1};

	ctrl = (t_control *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		if (prev_press.x != x || prev_press.y != y)
		{
			ctrl->fractol.anchor =
					get_complex_from_point(&(ctrl->fractol), x, y);
			prev_press.x = x;
			prev_press.y = y;
		}
		ctrl->fractol.zoom *= (button == SCROLL_UP) ? 0.9 : 1.1;
		if (no_render >= 3)
		{
			no_render = 0;
			render(ctrl);
		}
		else
			++no_render;
	}
	return (0);
}

int		handle_mouse_release(int button, int x, int y, void *param)
{
	t_control		*ctrl;

	ctrl = (t_control *)param;
	if (button == L_CLICK)
	{
		ctrl->fractol.anchor = get_complex_from_point(&(ctrl->fractol), x, y);
		render(ctrl);
	}
	return (OK);
}

int		handle_mouse_move(int x, int y, void *param)
{
	t_control		*ctrl;
	static t_u32	no_render = 1;
	t_u32			mouse_speed;

	ctrl = (t_control *)param;
	if (!(ctrl->fractol.is_static))
	{
		if (ctrl->fractol.type == newton)
			ctrl->fractol.param =
					get_complex_from_point(&(ctrl->fractol), x, y);
		else
			ctrl->fractol.iter_cpoly.coefs[ctrl->cur_deg] =
					get_complex_from_point(&(ctrl->fractol), x, y);
		mouse_speed = (ctrl->mouse.x - x) * (ctrl->mouse.x - x)
					+ (ctrl->mouse.y - y) * (ctrl->mouse.y - y);
		if (no_render >= 5 * mouse_speed || (mouse_speed < 4 && no_render >= 5))
		{
			no_render = 0;
			render(ctrl);
		}
		else
			++no_render;
	}
	ctrl->mouse.x = x;
	ctrl->mouse.y = y;
	return (OK);
}
