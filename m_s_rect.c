/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_s_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 05:14:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/02 05:14:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** rect_w_h is the number of rows and columns in the rectangle's pixels
**
** stores two horizontal lines then two vertical lines without the pixels
** already accounted for
*/

static t_figure		get_rect_points(t_point anchor, t_point rect_w_h)
{
	t_figure	res;
	int			i;

	if ((i = anchor.x + rect_w_h.x - REN_W) >= 0)
		rect_w_h.x -= i;
	if ((i = anchor.y + rect_w_h.y - REN_H) >= 0)
		rect_w_h.y -= i;
	res.pt_lst_len = 2 * rect_w_h.y + 2 * (rect_w_h.x) - 4;
	if (!(res.pt_lst = (t_point *)ft_memalloc(sizeof(t_point) * res.pt_lst_len)))
		exit_error("memalloc failure in get_rect_points", 0);
	i = -1;
	while (++i < rect_w_h.x)
	{
		res.pt_lst[i].x = anchor.x + i;
		res.pt_lst[i].y = anchor.y;
		res.pt_lst[i + rect_w_h.x].x = anchor.x + i;
		res.pt_lst[i + rect_w_h.x].y = anchor.y + rect_w_h.y - 1;
	}
	while (i < res.pt_lst_len) //fix this loop to imitate the previous for a line ?
	{
		res.pt_lst[i].x = anchor.x;
		res.pt_lst[i].y = anchor.y + 1 + i;
		++i;
		res.pt_lst[i].x = anchor.x + rect_w_h.x - 1; //++i for a line here
		res.pt_lst[i].y = anchor.y + i;
		++i;
	}
	return (res);
}

/*
** Returns 1 if no subrectangles and fill is required, returns 1 if
** subrectangles need to be made.
*/

static int 			trace_dwell_rect(t_control *ctrl,
									t_u8 dwell_arr[REN_H][REN_W],
									t_point anchor, t_point rect_w_h)
{
	t_figure	fig;
	t_u8		first_dwell;
	int			i;
	t_u8		unique_color;
	t_point		tmp;

	if ((first_dwell = dwell_arr[anchor.y][anchor.x]) == 0)
	{
		first_dwell = get_dwell_from_point(ctrl, anchor);
		dwell_arr[anchor.y][anchor.x] = first_dwell;
	}
	unique_color = first_dwell;
	if (rect_w_h.x <= 1 && rect_w_h.y <= 1)
		return (unique_color);
	fig = get_rect_points(anchor, rect_w_h);
	i = -1;
	while (++i < fig.pt_lst_len)
	{
		tmp = fig.pt_lst[i];
		if (dwell_arr[tmp.y][tmp.x] == 0)
			dwell_arr[tmp.y][tmp.x] = get_dwell_from_point(ctrl, tmp);
		if (unique_color && dwell_arr[tmp.y][tmp.x] != first_dwell)
			unique_color = 0;
	}
	free(fig.pt_lst);
	return (unique_color);
}

static void			fill_dwell_rect(t_u8 dwell_arr[REN_H][REN_W], t_u8 dwell,
									t_point anchor, t_point rect_w_h)
{
	int		tmp;
	t_point	end;

	if ((tmp = anchor.x + rect_w_h.x - REN_W) >= 0)
		rect_w_h.x -= tmp;
	if ((tmp = anchor.y + rect_w_h.y - REN_H) >= 0)
		rect_w_h.y -= tmp;
	end.x = rect_w_h.x + anchor.x;
	end.y = rect_w_h.y + anchor.y;
	tmp = anchor.x;
	while (anchor.y < end.y)
	{
		anchor.x = tmp;
		while (anchor.x < end.x)
			dwell_arr[anchor.y][(anchor.x)++] = dwell;
		++(anchor.y);
	}
}

static void			rect_fill_or_divide(t_control *ctrl,
										t_u8 dwell_arr[REN_H][REN_W],
										t_point anchor, t_point rect_w_h)
{
	t_u8		dwell;

	if ((dwell = trace_dwell_rect(ctrl, dwell_arr, anchor, rect_w_h)))
		fill_dwell_rect(dwell_arr, dwell, anchor, rect_w_h);
	else
		rect_subdivider(ctrl, dwell_arr, anchor, rect_w_h);
}

void				rect_subdivider(t_control *ctrl,
									t_u8 dwell_arr[REN_H][REN_W],
									t_point anchor, t_point rect_w_h)
{
	t_point		sub_anc;
	t_point		sub_w_h;

	if (rect_w_h.x == 0 || rect_w_h.y == 0)
		return ;
	sub_w_h.x = rect_w_h.x / 2;
	sub_w_h.y = rect_w_h.y / 2;
	sub_anc = anchor;
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.x += sub_w_h.x;
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.y += sub_w_h.y;
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.x -= sub_w_h.x;
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
}
