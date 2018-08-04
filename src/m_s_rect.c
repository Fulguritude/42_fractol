/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_s_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 05:14:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/08/04 16:30:57 by fulguritu        ###   ########.fr       */
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
	first_dwell = dwell_arr[anchor.y][anchor.x] % MAX_DWELL;
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
		if (unique_color && dwell_arr[tmp.y][tmp.x] % MAX_DWELL != first_dwell)
			unique_color = 0;
	}
//printf("end rect_trace\n");
	free(fig.pt_lst);
	return (unique_color);
}

static void			fill_dwell_rect(t_u8 dwell_arr[REN_H][REN_W], t_u8 dwell,
									t_point anchor, t_point rect_w_h)
{
	static int	squares = SHOW_MS_SQUARES;
	t_point		start;
	t_point		end;

//printf("rect_fill\n");
	if ((end.x = anchor.x + rect_w_h.x) - REN_W > 0)
		rect_w_h.x -= end.x - REN_W;
	if ((end.y = anchor.y + rect_w_h.y) - REN_H > 0)
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
				dwell_arr[anchor.y][anchor.x] += MAX_DWELL;
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

//printf("anchor: %d %d ; rect_w_h: %d %d\n", anchr.x, anchr.y, rect_w_h.x, rect_w_h.y);
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
	int			rx_even;
	int			ry_even;

//printf("rect_sub: rect_wh.x: %d | rect_wh.y: %d\n", rect_w_h.x, rect_w_h.y);

//if (rect_w_h.x == 2 && rect_w_h.y == 2)
//exit_error("y u infloop", 0);
//float depth = rect_w_h.y ? ft_logn(REN_H / rect_w_h.y, 2) : -1;
//char *tabs = depth != -1 ? ft_strcnew(depth, ' ') : NULL;
//char *tabs = " ";
//printf("\tdepth = %f\n", depth);

	if (rect_w_h.x <= 2 || rect_w_h.y <= 2)//|| depth > 2)
		return ;
	rx_even = !(rect_w_h.x % 2);
	ry_even = !(rect_w_h.y % 2);
	sub_w_h.x = rect_w_h.x / 2 + 1;
	sub_w_h.y = rect_w_h.y / 2 + 1;
	sub_anc = anchor;
//printf("%s1 - subanc: (%3d, %3d) | rect_w_h : (%3d, %3d) | sum: (%3d, %3d)\n", tabs, sub_anc.x, sub_anc.y, sub_w_h.x, sub_w_h.y, sub_anc.x + sub_w_h.x, sub_anc.y + sub_w_h.y);
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.x += sub_w_h.x - 1;
	sub_w_h.x -= rx_even;
//printf("%s2 - subanc: (%3d, %3d) | rect_w_h : (%3d, %3d) | sum: (%3d, %3d)\n", tabs, sub_anc.x, sub_anc.y, sub_w_h.x, sub_w_h.y, sub_anc.x + sub_w_h.x, sub_anc.y + sub_w_h.y);
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_anc.y += sub_w_h.y - 1;
	sub_w_h.y -= ry_even;
//printf("%s3 - subanc: (%3d, %3d) | rect_w_h : (%3d, %3d) | sum: (%3d, %3d)\n", tabs, sub_anc.x, sub_anc.y, sub_w_h.x, sub_w_h.y, sub_anc.x + sub_w_h.x, sub_anc.y + sub_w_h.y);
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
	sub_w_h.x += rx_even;
	sub_anc.x -= sub_w_h.x - 1;
//printf("%s4 - subanc: (%3d, %3d) | rect_w_h : (%3d, %3d) | sum: (%3d, %3d)\n", tabs, sub_anc.x, sub_anc.y, sub_w_h.x, sub_w_h.y, sub_anc.x + sub_w_h.x, sub_anc.y + sub_w_h.y);
	rect_fill_or_divide(ctrl, dwell_arr, sub_anc, sub_w_h);
//if (tabs)
//	free(tabs);
}


/*
//working version with double-lines

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
}*/
