/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 20:49:10 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/05 19:38:36 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	handle_key_palette(int key, t_control *ctrl)
{
	int		status;

	status = -1;
	if (key == KEY_NUMPAD_0)
		status = 0;
	else if (key == KEY_NUMPAD_1)
		status = 1;
	else if (key == KEY_NUMPAD_2)
		status = 2;
	else if (key == KEY_NUMPAD_3)
		status = 3;
	else if (key == KEY_NUMPAD_4)
		status = 4;
	else if (key == KEY_NUMPAD_5)
		status = 5;
	else if (key == KEY_NUMPAD_6)
		status = 6;
	else if (key == KEY_NUMPAD_7)
		status = 7;
	else if (key == KEY_NUMPAD_8)
		status = 8;
	else if (key == KEY_NUMPAD_9)
		status = 9;
	ctrl->fractol.palette = status == -1 ? ctrl->fractol.palette : status;
	return (status != -1);
}

static int	handle_key_window(int key, t_control *ctrl)
{
	int					status;
	static t_float		zoom_trans_ratio = 0.04;

	status = 1;
	if (key == KEY_RIGHT)
		ctrl->fractol.anchor.re -= zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_LEFT)
		ctrl->fractol.anchor.re += zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_UP)
		ctrl->fractol.anchor.im += zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_DOWN)
		ctrl->fractol.anchor.im -= zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_PAGE_UP)
		ctrl->fractol.zoom *= 1.25;
	else if (key == KEY_PAGE_DN)
		ctrl->fractol.zoom *= 0.8;
	else if (key == KEY_LCTRL)
		ctrl->debug = !(ctrl->debug);
	else if (key == KEY_RCTRL)
		ctrl->render_mode = (ctrl->render_mode + 1) == 3 ?
									0 : ctrl->render_mode + 1;
	else
		status = 0;
	return (status);
}

static int	handle_key_cpoly(int key, t_control *ctrl)
{
	int		status;
	char	*str;

	status = 1;
	if (key == KEY_NUMPAD_ADD && ctrl->fractol.cur_coef < MAX_DEGREE)
		++(ctrl->fractol.cur_coef);
	else if (key == KEY_NUMPAD_SUB &&
			ctrl->fractol.cur_coef > -(ctrl->fractol.type == newton))
		--(ctrl->fractol.cur_coef);
	else if (key == KEY_NUMPAD_ENTER)
		ctrl->fractol.iter_cpoly.deg = ctrl->fractol.cur_coef;
	else
		status = 0;
	if (ctrl->fractol.cur_coef > ctrl->fractol.iter_cpoly.deg)
		ctrl->fractol.iter_cpoly.deg = ctrl->fractol.cur_coef;
	if (key == KEY_END)
	{
		ft_putendl(str = cpoly_to_str(&(ctrl->fractol.iter_cpoly)));
		free(str);
		ft_putendl(str = cpoly_to_polyobj(&(ctrl->fractol.iter_cpoly)));
		free(str);
		ft_printf("param (only newton): (%a, %a)\n",
				ctrl->fractol.param.re, ctrl->fractol.param.im);
	}
	return (status);
}

int			handle_key(int key, void *param)
{
	t_control			*ctrl;
	int					has_changed;

	ctrl = (t_control *)param;
	has_changed = handle_key_palette(key, ctrl);
	has_changed = has_changed || handle_key_window(key, ctrl);
	has_changed = has_changed || handle_key_cpoly(key, ctrl);
	if (key == KEY_ESC)
		exit_error("Software closing.", 0);
	else if (key == KEY_SPACE)
		ctrl->fractol.is_static = !(ctrl->fractol.is_static);
	else if (key == KEY_HOME)
		ctrl->show_m_s = !(ctrl->show_m_s);
	else if (key == KEY_NUMPAD_MUL)
		ctrl->fractol.radius_sqrd *= 1.25;
	else if (key == KEY_NUMPAD_DIV)
		ctrl->fractol.radius_sqrd *= 0.8;
	else if (!has_changed)
		return (1);
	render(ctrl);
	return (0);
}
