/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dwell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 00:56:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/08/04 16:26:31 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline t_u8		get_dwell_from_point(t_control *ctrl, t_point pt)
{
	return (ctrl->fractol.dwell_func(
					&(ctrl->fractol),
					get_complex_from_point(&(ctrl->fractol), pt.x, pt.y)));
}

/*
**	return (dwl << R_OFFSET | dwl << G_OFFSET | dwl << B_OFFSET);
**	return (dwl << R_OFFSET | dwl << G_OFFSET);
*/

t_u32		get_color_from_dwell(t_control *ctrl, t_u8 dwl)
{
	if (ctrl->fractol.palette == 0)
		return (dwl == MAX_DWELL ? BLACK : WHITE);
	else if (ctrl->fractol.palette == 1)
		return (dwl << R_OFFSET);
	else if (ctrl->fractol.palette == 2)
		return (dwl << G_OFFSET);
	else if (ctrl->fractol.palette == 3)
		return (dwl << B_OFFSET);
	else if (ctrl->fractol.palette == 4)
		return (dwl << R_OFFSET | dwl << G_OFFSET | dwl << (B_OFFSET - 1));
	else if (ctrl->fractol.palette == 5)
		return (dwl << R_OFFSET | dwl << (G_OFFSET - 1) | dwl << B_OFFSET);
	else if (ctrl->fractol.palette == 6)
		return (dwl << (R_OFFSET - 1) | dwl << G_OFFSET | dwl << B_OFFSET);
	else if (ctrl->fractol.palette == 7)
		return (dwl << R_OFFSET | dwl << G_OFFSET | dwl << (B_OFFSET + 1));
	else if (ctrl->fractol.palette == 8)
		return (dwl << R_OFFSET | dwl << (G_OFFSET + 1) | dwl << B_OFFSET);
	else if (ctrl->fractol.palette == 9)
		return (dwl << (R_OFFSET + 1) | dwl << G_OFFSET | dwl << B_OFFSET);
	return (RED);
}

/*
** ugly trick putting the ++y in the if at the end... should be:
**		if (++x == REN_W)
**		{
**			++y;
**			x = 0;
**		}
**
** ugly trick is
**		if (++x == REN_W && ++y)
**			x = 0;
*/

void			dwell_arr_to_img(t_control *ctrl, t_u8 dwell_arr[REN_H][REN_W])
{
	static int	squares = SHOW_MS_SQUARES;
	int			palette[MAX_DWELL + 1];
	int			i;
	int			x;
	int			y;

	i = -1;
	while (++i < MAX_DWELL)
		palette[i] = get_color_from_dwell(ctrl, i);
	palette[MAX_DWELL] = ctrl->show_m_s ? WHITE : BLACK;
	i = 0;
	y = 0;
	x = 0;
	while (i < ctrl->img_pixel_nb)
	{
		if (dwell_arr[y][x] > MAX_DWELL)
			dwell_arr[y][x] = squares ? MAX_DWELL : dwell_arr[y][x] - MAX_DWELL;
		((t_u32 *)ctrl->img_data)[i] = palette[dwell_arr[y][x]];
		++i;
		if (++x == REN_W)
		{
			++y;
			x = 0;
		}
	}
}
