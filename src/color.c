/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 01:38:35 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/02 01:38:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				handle_key_palette(int key, t_control *ctrl)
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

/*
**	return (dwell << R_OFFSET | dwell << G_OFFSET | dwell << B_OFFSET);
**	return (dwell << R_OFFSET | dwell << G_OFFSET);
*/

t_u32		get_color_from_dwell(t_control *ctrl, t_u8 dwell)
{
	if (ctrl->fractol.palette == 0)
		return (dwell == MAX_DWELL ? BLACK : WHITE);
	else if (ctrl->fractol.palette == 1)
		return (dwell << R_OFFSET);
	else if (ctrl->fractol.palette == 2)
		return (dwell << G_OFFSET);
	else if (ctrl->fractol.palette == 3)
		return (dwell << B_OFFSET);
	else if (ctrl->fractol.palette == 4)
		return (dwell << R_OFFSET | dwell << G_OFFSET | dwell << (B_OFFSET - 1));
	else if (ctrl->fractol.palette == 5)
		return (dwell << R_OFFSET | dwell << (G_OFFSET - 1) | dwell << B_OFFSET);
	else if (ctrl->fractol.palette == 6)
		return (dwell << (R_OFFSET - 1) | dwell << G_OFFSET | dwell << B_OFFSET);
	else if (ctrl->fractol.palette == 7)
		return (dwell << R_OFFSET | dwell << G_OFFSET | dwell << (B_OFFSET + 1));
	else if (ctrl->fractol.palette == 8)
		return (dwell << R_OFFSET | dwell << (G_OFFSET + 1) | dwell << B_OFFSET);
	else if (ctrl->fractol.palette == 9)
		return (dwell << (R_OFFSET + 1) | dwell << G_OFFSET | dwell << B_OFFSET);
	return (RED);
}
