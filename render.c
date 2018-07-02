/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 05:08:16 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/02 05:08:24 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		render_seq(t_control *ctrl)
{
	t_point		tmp;
	int			color;
	t_s32		x;
	t_s32		y;
	t_u8		dwell;

//printf("REN_H = %d, REN_W = %d\n", REN_H, REN_W);
	y = -1;
	while (++y < REN_H)
	{
		x = -1;
		while (++x < REN_W)
		{
			tmp.x = x;
			tmp.y = y;
			dwell = get_dwell_from_point(ctrl, tmp);
			color = get_color_from_dwell(dwell);
			mlximg_setpixel(ctrl, dwell == ctrl->fractol.max_dwell ?
										BLACK : color, x, y);
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}

//point to bounds
//fill figure
//keep tracer function signatures coherent, start with a basic rectangle trace.
//should have an anchor for the figure, and a be a protocol for finding point.
//octave cat

/* 
** To implement mariani silver, one must trace the boundaries of a figure to
** analyze if there are different dwells and then regular subtiles where the
** same algorithm is ran but some sides are already calculated. If all sides of
** the figure have the same dwell, the figure's inside is assumed to be
** detail-less and colored with that dwell.
*/

static void		dwell_arr_to_img(t_control *ctrl, t_u8 dwell_arr[REN_H][REN_W])
{
	int		palette[ctrl->fractol.max_dwell];
	t_u32	i;
	t_u32	pix_len;
	int		x;
	int		y;

	i = 0;
	while (i < ctrl->fractol.max_dwell)
	{
		palette[i] = get_color_from_dwell(i);
		++i;
	}
	i = 0;
	pix_len = REN_W * REN_H;
	y = 0;
	x = 0;
	while (i < pix_len)
	{
		((t_u32 *)ctrl->img_data)[i] = palette[dwell_arr[y][x]];
		++i;
		if (++x == REN_W)
		{
			++y;
			x = 0;
		}
	}
}

static int		render_m_s(t_control *ctrl)
{
	static t_u8			dwell_arr[REN_H][REN_W];
	static t_point		init_anchor = {0, 0};
	static t_point		init_rect_size = {REN_W, REN_H};

	ft_bzero(dwell_arr, sizeof(t_u8) * REN_H * REN_W);
	rect_subdivider(ctrl, dwell_arr, init_anchor, init_rect_size);
	dwell_arr_to_img(ctrl, dwell_arr);
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}

int				render(void *param)
{
	t_control	*ctrl;

	ctrl = (t_control *)param;

if (ctrl->fractol.type == newton) {
char *str = cpolyfrac_to_str(&(ctrl->fractol.iter_cpolyfrac));
printf("cpolyfrac: \n%s\n", str);
printf("param: (%f, %f)\n", ctrl->fractol.param.re, ctrl->fractol.param.im);
free(str);
} else {
char *str = cpoly_to_str(&(ctrl->fractol.iter_cpoly));
printf("cpoly: %s\n", str);
free(str);
}
	if (ctrl->render_mode == 0)
		return (render_seq(ctrl));
	else
		return (render_m_s(ctrl));
}
