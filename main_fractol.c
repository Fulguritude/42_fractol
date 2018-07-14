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
	int		i;

	if (e_no == 0)
	{
		i = write(1, e_msg, ft_strlen(e_msg));
		i += write(1, "\n", 1);
		exit(i);
	}
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
	ctrl->render_mode = 1;
}


static void		init_fractol(t_control *ctrl, t_fractal fractal,
								char const *fpath)
{
	t_fractol	res;

	res.type = fractal;
	res.zoom = 5.;
	res.radius = fractal == newton ? 1. : 2.; //TODO verif
	res.radius_sqrd = fractal == newton ? 1. : 4.;
	res.anchor.re = 0.;
	res.anchor.im = 0.;
	res.is_static = fractal == julia ? 0 : 1;
	res.iter_cpoly = get_cpoly_from_filepath(fpath);
	res.dwell_func = fractal == julia ? &julia_dwell : &mandel_dwell;
	res.dwell_func = fractal == burningship ? &burningship_dwell : res.dwell_func;
	if (fractal == newton)
	{
		res.iter_cpolyfrac = set_cpolyfrac(res.iter_cpoly, derive_cpoly(res.iter_cpoly));
		res.param = (t_complex){1.0, 0.};
		res.dwell_func = &newton_dwell;
	}
/*	else if (fractal == newtonroot)
	{
		ctrl->fractol.iter_cpoly = 
	}*/
	ctrl->fractol = res;
}

/*
** || !ft_strequ(argv[1], "julia") ||
**		!ft_strequ(argv[1], "hofstadter") || !ft_strequ(argv[1], "mandelbrot"
*/

int				main(int argc, char **argv)
{
	t_control	ctrl;

	if (argc != 2 && argc != 3)
		exit_error("usage: \"./fractol [arg]\"\nValid arguments are \"julia\","
			"\"mandelbrot\" and \"newton\".\n", 0);
	init_mlx(&ctrl);
	if (ft_strequ(argv[1], "julia"))
		init_fractol(&ctrl, julia, argc > 2 ? argv[2] : CPOLY_DIR"julia");
	else if (ft_strequ(argv[1], "mandelbrot"))
		init_fractol(&ctrl, mandelbrot, argc > 2 ? argv[2] : CPOLY_DIR"mandelbrot");
	else if (ft_strequ(argv[1], "newton"))
		init_fractol(&ctrl, newton, argc > 2 ? argv[2] : CPOLY_DIR"newton");
	else if (ft_strequ(argv[1], "burningship"))
		init_fractol(&ctrl, burningship, argc > 2 ? argv[2] : CPOLY_DIR"mandelbrot");
//	else if (ft_strequ(argv[1], "newtonroot"))
//		init_fractol(&ctrl, newtonroot, argc > 2 ? argv[2] : CPOLY_DIR"newtonroot");
	else
		exit_error("Valid arguments are \"julia\","
			"\"mandelbrot\", \"burningship\" and \"newton\".\n", 0);
	init_events(&ctrl);
	render(&ctrl);
	mlx_loop(ctrl.mlx_ptr);
	return (0);
}
