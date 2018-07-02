/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fractol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 14:28:29 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/17 14:28:30 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			toggle_debug(t_control *ctrl)
{
	ctrl->debug = !(ctrl->debug);
}

void			exit_error(char *e_msg, int e_no)
{
	if (e_no == 0)
		write(1, e_msg, ft_strlen(e_msg));
	else
		perror(e_msg);
	exit(e_no);
}

/*
** Bits per pixel (32, each color is an int) are immediately converted to
** bytes per pixel.
**
** Anchor is which point of the complex plane is the center of the window.
*/

static void		init_mlx(t_control *ctrl)
{
	ctrl->debug = 1;
	if (!(ctrl->mlx_ptr = mlx_init()))
		exit_error("could not init mlx_ptr", 0);
	if (!(ctrl->win_ptr = mlx_new_window(ctrl->mlx_ptr,
				WIN_W, WIN_H, "Fract'ol")))
		exit_error("could not init win_ptr", 0);
	if (!(ctrl->img_ptr = mlx_new_image(ctrl->mlx_ptr, REN_W, REN_H)))
		exit_error("could not init img_ptr", 0);
	if (!(ctrl->img_data = mlx_get_data_addr(ctrl->img_ptr, &(ctrl->img_bpp),
										&(ctrl->img_bpl), &(ctrl->endian))))
		exit_error("could not retrieve img data ptr and other info", 0);
	ctrl->img_bpp = ctrl->img_bpp / 8;
	ctrl->img_bytelen = ctrl->img_bpp * REN_H * REN_W;
	ctrl->render_mode = 0;
}


static void		init_fractol(t_control *ctrl, t_fractal fractal)
{
	t_fractol	res;
	t_cpoly		cpoly;

	res.type = fractal;
	res.max_dwell = INIT_MAX_DWELL;
	res.zoom = 5.;
	res.radius = 2.;
	res.radius_sqrd = 4.;
	res.anchor.re = 0.;
	res.anchor.im = 0.;
	res.is_static = fractal == julia ? 0 : 1;
	cpoly.deg = 2;
	ft_bzero(cpoly.coefs, 256 * sizeof(t_complex));
	cpoly.coefs[2].re = 1.;
	cpoly.coefs[0].re = fractal == julia ? 0.5 : 0.;
	cpoly.coefs[0].im = fractal == julia ? 0.5 : 0.;
	res.iter_cpoly = cpoly;
	ctrl->fractol = res;
	ctrl->dwell_func = fractal == julia ? &julia_dwell : &mandel_dwell;
	if (fractal == newton)
	{
		cpoly.deg = 3;
		cpoly.coefs[3].re = 1.;
		cpoly.coefs[0].re = -1.;
		cpoly.coefs[2].re = 0.;
		ctrl->fractol.iter_cpolyfrac = set_cpolyfrac(cpoly, derive_cpoly(cpoly));
		ctrl->fractol.param = (t_complex){0.5, 0.5};
		ctrl->dwell_func = &newton_dwell;
	}
}

/*
** || !ft_strequ(argv[1], "julia") ||
**		!ft_strequ(argv[1], "hofstadter") || !ft_strequ(argv[1], "mandelbrot"
*/

int				main(int argc, char **argv)
{
	t_control	ctrl;

	if (argc != 2)
		exit_error("usage: \"./fractol [arg]\"\nValid arguments are \"julia\","
			"\"mandelbrot\" and \"newton\".\n", 0);
	init_mlx(&ctrl);
	if (ft_strequ(argv[1], "julia"))
		init_fractol(&ctrl, julia);
	else if (ft_strequ(argv[1], "mandelbrot"))
		init_fractol(&ctrl, mandelbrot);
	else if (ft_strequ(argv[1], "newton"))
		init_fractol(&ctrl, newton);
	else
		exit_error("Valid arguments are \"julia\","
			"\"mandelbrot\" and \"newton\".\n", 0);
	init_events(&ctrl);
	render(&ctrl);
	mlx_loop(ctrl.mlx_ptr);
	return (0);
}
