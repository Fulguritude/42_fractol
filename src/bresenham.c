/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 23:41:50 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/17 23:41:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** TODO: optimize draw_vert and draw_horz by allowing them to swap end and start
**			in order to always iterate the same way ?
*/

static int		draw_vert(t_point *res_lst, t_point start, int endy)
{
	int		inc;
	int		y;

	inc = start.y < endy ? 1 : -1;
	y = start.y + inc;
	if (inc == 1)
		while (y <= endy && point_in_bounds(start.x, y))
		{
			res_lst[ft_abs(y - start.y)] = (t_point){start.x, y};
			y += inc;
		}
	else
		while (y >= endy && point_in_bounds(start.x, y))
		{
			res_lst[ft_abs(y - start.y)] = (t_point){start.x, y};
			y += inc;
		}
	return (ft_abs(y - start.y));
}

static int		draw_horz(t_point *res_lst, t_point start, int endx)
{
	int		inc;
	int		x;

	inc = start.x < endx ? 1 : -1;
	x = start.x + inc;
	if (inc == 1)
		while (x <= endx && point_in_bounds(x, start.y))
		{
			res_lst[ft_abs(x - start.x)] = (t_point){x, start.y};
			x += inc;
		}
	else
		while (x >= endx && point_in_bounds(x, start.y))
		{
			res_lst[ft_abs(x - start.x)] = (t_point){x, start.y};
			x += inc;
		}
	return (ft_abs(x - start.x));
}

static int		draw_vertoct(t_point *res_lst, t_point start, 
							 t_point end, t_point d)
{
	int		x;
	int		y;
	int		xinc;
	int		yinc;
	int		acc_er;

	x = start.x;
	y = start.y;
	acc_er = 0;
	xinc = x < end.x ? 1 : -1;
	yinc = y < end.y ? 1 : -1;
	while (y != end.y)
	{
	    acc_er += d.x;
	    if (acc_er >= d.y)
		{
			acc_er -= d.y;
			x += xinc;
		}
		if (!(point_in_bounds(x, y)))
			break ;
		res_lst[ft_abs(y - start.y)] = (t_point){x, y};
		y += yinc;
	}
	return (ft_abs(y - start.y));
}

static int		draw_horzoct(t_point *res_lst, t_point start,
							 t_point end, t_point d)
{
	int		x;
	int		y;
	int		xinc;
	int		yinc;
	int		acc_er;

	x = start.x;
	y = start.y;
	acc_er = 0;
	xinc = x < end.x ? 1 : -1;
	yinc = y < end.y ? 1 : -1;
	while (x != end.x)
	{
	    acc_er += d.y;
	    if (acc_er >= d.x)
		{
			acc_er -= d.x;
			y += yinc;
		}
		if (!(point_in_bounds(x, y)))
			break ;
		res_lst[ft_abs(x - start.x)] = (t_point){x, y};
		x += xinc;
	}
	return (ft_abs(x - start.x));
}

/*
** Dirty trick to gain a few lines:
**
**	if (d.x == 0 && d.y == 0)
**	{
**		res_lst[0] = start;
**		res_lst_len = 1;
**	}
** =>
**
**	if (d.x == 0 && d.y == 0 && (res_lst_len = 1))
**		res_lst[0] = start;
*/

t_figure		get_line_points(t_point start, t_point end)
{
	t_figure			fig;
	t_point				d;
	static t_point		res_lst[REN_W * REN_H];
	int					res_lst_len;

	res_lst[0] = (t_point){start.x, start.y};
	d.x = ft_abs((end.x - start.x) * 2);
	d.y = ft_abs((end.y - start.y) * 2);
	fig.pt_lst = NULL;
	fig.pt_lst_len = -1;
	if (d.x == 0 && d.y == 0)
	{
		res_lst[0] = start;
		res_lst_len = 1;
	}
	else if (d.x == 0)
		res_lst_len = draw_vert(res_lst, start, end.y);
	else if (d.y == 0)
		res_lst_len = draw_horz(res_lst, start, end.x);
	else if (d.x < d.y)
		res_lst_len = draw_vertoct(res_lst, start, end, d);
	else
		res_lst_len = draw_horzoct(res_lst, start, end, d);
	fig.pt_lst_len = res_lst_len;
	if (!(fig.pt_lst = (t_point *)malloc(sizeof(t_point) * res_lst_len)))
		exit_error("bresenham: malloc failure: ", errno);
	while (--res_lst_len >= 0)
		fig.pt_lst[res_lst_len] = res_lst[res_lst_len];
//printf("allocated = %p\n", fig.pt_lst); 
	return (fig);
}
