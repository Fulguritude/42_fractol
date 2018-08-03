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

//printf("rect_trace\n");
	if (dwell_arr[anchor.y][anchor.x] == 0)
		dwell_arr[anchor.y][anchor.x] = get_dwell_from_point(ctrl, anchor);
	first_dwell = dwell_arr[anchor.y][anchor.x];
	unique_color = first_dwell;
	if (rect_w_h.x <= 1 && rect_w_h.y <= 1)
		return (unique_color);
//	fig.pt_lst_len = -1;
//	fig.pt_lst = NULL;
	fig = get_rect_points(anchor, rect_w_h);
//printf("fig.len = %d| fig.lst = %p\n", fig.pt_lst_len, fig.pt_lst);
	i = -1;
	while (++i < fig.pt_lst_len)
	{
		tmp = fig.pt_lst[i];
		if (dwell_arr[tmp.y][tmp.x] == 0)
			dwell_arr[tmp.y][tmp.x] = get_dwell_from_point(ctrl, tmp);
		if (unique_color && dwell_arr[tmp.y][tmp.x] != first_dwell)
			unique_color = 0;
	}
//printf("end rect_trace\n");
	free(fig.pt_lst);
	return (unique_color);
}

static void			fill_dwell_rect(t_u8 dwell_arr[REN_H][REN_W], t_u8 dwell,
									t_point anchor, t_point rect_w_h)
{
	static int	squares = 1;
	t_point		start;
	t_point		end;

//printf("rect_fill\n");
	if ((end.x = anchor.x + rect_w_h.x) - REN_W >= 0)
		rect_w_h.x -= end.x - REN_W;
	if ((end.y = anchor.y + rect_w_h.y) - REN_H >= 0)
		rect_w_h.y -= end.y - REN_H;
	start.x = anchor.x;
	start.y = anchor.y;
	while (anchor.y < end.y)
	{
		anchor.x = start.x;
		while (anchor.x < end.x)
		{
			dwell_arr[anchor.y][anchor.x] = dwell;
			//add condition for more than a single pixel filled to avoid black spots ?
			if (squares && !(rect_w_h.x <= 2 || rect_w_h.y <= 2) && 
							(anchor.y == start.y || anchor.y == end.y - 1 || 
							anchor.x == start.x || anchor.x == end.x - 1))
				dwell_arr[anchor.y][anchor.x] = MAX_DWELL;
			++(anchor.x);
		}
		++(anchor.y);
	}
}

static void			rect_fill_or_divide(t_control *ctrl,
										t_u8 dwell_arr[REN_H][REN_W],
										t_point anchr, t_point rect_w_h)
{
	t_u8		tmp;
	int			i;

//printf("anchor: %d %d ; rect_w_h: %d %d\n", anchr.x, anchr.y, rect_w_h.x, rect_w_h.y);
	if (rect_w_h.x == 1 || rect_w_h.y == 1)
	{
		if (rect_w_h.x == 1 && rect_w_h.y == 1)
			dwell_arr[anchr.y][anchr.x] = get_dwell_from_point(ctrl, anchr);
		else
		{
			tmp = (rect_w_h.x == 1);
			i = -1;
			while (++i < (tmp ? rect_w_h.y : rect_w_h.x))
			{
				tmp ? ++(anchr.y) : ++(anchr.x);
				dwell_arr[anchr.y][anchr.x] = get_dwell_from_point(ctrl, anchr);
			}
		}
		return ;
	}
	if ((tmp = trace_dwell_rect(ctrl, dwell_arr, anchr, rect_w_h)))
	{
		fill_dwell_rect(dwell_arr, tmp, anchr, rect_w_h);
		if (ctrl->show_m_s)
		{
			dwell_arr_to_img(ctrl, dwell_arr);
			mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr,
								0, 0);
//			usleep(200);
		}
	}
	else
		rect_subdivider(ctrl, dwell_arr, anchr, rect_w_h);
/*if (ctrl->show_m_s)
{
dwell_arr_to_img(ctrl, dwell_arr);
mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr,
						0, 0);
//		usleep(200);
}*/
}

void				rect_subdivider(t_control *ctrl,
									t_u8 dwell_arr[REN_H][REN_W],
									t_point anchor, t_point rect_w_h)
{
	t_point		sub_anc;
	t_point		sub_w_h;

//printf("rect_sub\n");
	if (rect_w_h.x <= 0 || rect_w_h.y <= 0)
		return ;
	sub_w_h.x = rect_w_h.x / 2;
	sub_w_h.y = rect_w_h.y / 2;
	sub_anc = anchor;
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.x += sub_w_h.x;
	sub_w_h.x += (rect_w_h.x % 2 && rect_w_h.x != 1);
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.y += sub_w_h.y;
	sub_w_h.y += (rect_w_h.y % 2 && rect_w_h.y != 1);
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_w_h.x -= (rect_w_h.x % 2 && rect_w_h.x != 1);
	sub_anc.x -= sub_w_h.x;
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
}
