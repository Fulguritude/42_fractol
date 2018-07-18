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

static void		show_debug_info(t_control *ctrl)
{
	char	*str;

	str = ctrl->render_mode ? "m-s" : "p-b-p";
	str = ctrl->render_mode == 2 ? "none" : str;
	ft_asprintf(&str, "render: %s", str);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 20, 20, GREEN, str);
	free(str);
	ft_asprintf(&str, "| is_static: %s", ctrl->fractol.is_static ? "T" : "F");
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 100, 20, GREEN, str);
	free(str);
	ft_asprintf(&str, "anchor: (%g, %g) | zoom: %g | cur_coef: %u",
			ctrl->fractol.anchor.re, ctrl->fractol.anchor.im,
			ctrl->fractol.zoom, ctrl->fractol.cur_coef);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 20, 40, GREEN, str);
	free(str);
	str = cpoly_to_str(&(ctrl->fractol.iter_cpoly));
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 20, 60, GREEN, str);
	free(str);
	if (ctrl->fractol.type != newton)
		return ;
	ft_asprintf(&str, "param: (%g, %g)", ctrl->fractol.param.re,
			ctrl->fractol.param.im);
	mlx_string_put(ctrl->mlx_ptr, ctrl->win_ptr, 40, 100, GREEN, str);
	free(str);
}

static int		render_seq(t_control *ctrl)
{
	t_point		tmp;
	int			color;
	t_s32		x;
	t_s32		y;
	t_u8		dwell;

	y = -1;
	while (++y < REN_H)
	{
		x = -1;
		while (++x < REN_W)
		{
			tmp.x = x;
			tmp.y = y;
			dwell = get_dwell_from_point(ctrl, tmp);
			color = get_color_from_dwell(ctrl, dwell);
			mlximg_setpixel(ctrl, dwell == MAX_DWELL ?
										BLACK : color, x, y);
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}

/*
** To implement mariani silver, one must trace the boundaries of a figure to
** analyze if there are different dwells and then regular subtiles where the
** same algorithm is ran but some sides are already calculated. If all sides of
** the figure have the same dwell, the figure's inside is assumed to be
** detail-less and colored with that dwell.
*/

/*
** ugly trick putting the ++y in the if at the end... should be:
**		if (++x == REN_W && ++y)
**		{
**			++y;
**			x = 0;
**		}
*/

static void		dwell_arr_to_img(t_control *ctrl, t_u8 dwell_arr[REN_H][REN_W])
{
	int		palette[MAX_DWELL + 1];
	t_u32	i;
	t_u32	pix_len;
	int		x;
	int		y;

	i = 0;
	while (i < MAX_DWELL)
	{
		palette[i] = get_color_from_dwell(ctrl, i);
		++i;
	}
	palette[MAX_DWELL] = BLACK;
	i = 0;
	pix_len = REN_W * REN_H;
	y = 0;
	x = 0;
	while (i < pix_len)
	{
		((t_u32 *)ctrl->img_data)[i] = palette[dwell_arr[y][x]];
		++i;
		if (++x == REN_W && ++y)
			x = 0;
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
	int			status;

	ctrl = (t_control *)param;
	if (ctrl->render_mode == 0)
		status = render_seq(ctrl);
	else if (ctrl->render_mode == 1)
		status = render_m_s(ctrl);
	else
	{
		mlximg_valset(ctrl, RED);
		status = 1;
	}
	if (ctrl->debug)
		show_debug_info(ctrl);
	return (status);
}
