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
