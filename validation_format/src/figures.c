/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 03:46:13 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/02 14:09:55 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline t_point		add_points(t_point const p1, t_point const p2)
{
	return ((t_point){p1.x + p2.x, p1.y + p2.y});
}

/*
** rect_w_h is the number of rows and columns in the rectangle's pixels
**
** stores two horizontal lines then two vertical lines without the pixels
** already accounted for
*/

t_figure			empty_figure(void)
{
	t_figure	res;

	res.pt_lst = NULL;
	res.pt_lst_len = -1;
	return (res);
}

t_figure			merge_figures(t_figure dest, t_figure src)
{
	t_figure	res;
	int			i;

	if ((!dest.pt_lst && !src.pt_lst)
		|| dest.pt_lst_len == -1 || src.pt_lst_len == -1)
		return (empty_figure());
	else if (!dest.pt_lst)
		return (src);
	else if (!src.pt_lst)
		return (dest);
	res.pt_lst_len = dest.pt_lst_len + src.pt_lst_len;
	if (!(res.pt_lst = (t_point *)malloc(sizeof(t_point) * res.pt_lst_len)))
		exit_error("merge_figures: malloc failure: ", 0);
	i = -1;
	while (++i < dest.pt_lst_len)
		res.pt_lst[i] = dest.pt_lst[i];
	while (i < dest.pt_lst_len + src.pt_lst_len)
	{
		res.pt_lst[i] = src.pt_lst[i - dest.pt_lst_len];
		++i;
	}
	free(dest.pt_lst);
	free(src.pt_lst);
	return (res);
}

static t_figure		get_rect_points_ysup3(t_figure tmp,
								t_point anchor, t_point rect_w_h)
{
	t_figure	res;

	res = merge_figures(tmp,
			get_line_points(
				add_points(anchor, (t_point){0, 1}),
				add_points(anchor, (t_point){0, rect_w_h.y - 2})));
	res = merge_figures(res,
			get_line_points(
				add_points(anchor, (t_point){rect_w_h.x - 1, 1}),
				add_points(anchor, (t_point){rect_w_h.x - 1, rect_w_h.y - 2})));
	return (res);
}

t_figure			get_rect_points(t_point anchor, t_point rect_w_h)
{
	t_figure	res;
	int			i;

	res = empty_figure();
	if ((i = anchor.x + rect_w_h.x - REN_W) > 0)
		rect_w_h.x -= i;
	if ((i = anchor.y + rect_w_h.y - REN_H) > 0)
		rect_w_h.y -= i;
	if (rect_w_h.x <= 0 || rect_w_h.y <= 0)
		return (res);
	if (rect_w_h.x == 1 && rect_w_h.y == 1)
		return (get_line_points(anchor, anchor));
	else
		res = get_line_points(
					anchor,
					add_points(anchor, (t_point){rect_w_h.x, 0}));
	if (rect_w_h.y >= 2)
		res = merge_figures(res,
				get_line_points(
					add_points(anchor, (t_point){0, rect_w_h.y - 1}),
					add_points(anchor, (t_point){rect_w_h.x, rect_w_h.y - 1})));
	if (rect_w_h.y >= 3)
		res = get_rect_points_ysup3(res, anchor, rect_w_h);
	return (res);
}
