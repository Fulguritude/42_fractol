#include "fractol.h"

int		get_julia_point_color(t_fractol frac, t_complex pt)
{
	t_u32		i;

	t_complex 	c;
	c.re = 0.5;
	c.im = 0.5;

	i = 0;
	while (i < frac.max_iter)
	{
		pt = c_add(c_mul(pt, pt), c);
		if (c_quadnorm(pt) > frac.radius_sqrd)
			return (i << 26 | i << 18 | i << 10);
		++i;
	}
	return (BLACK);
}

/*
	t_fractal	type;
	int			max_iter;
	t_complex	anchor;
	t_float		zoom;
	t_float		radius; //convergence norm
	t_float		radius_sqrd; //convergence quadratic norm
	t_poly		iter_func;
*/
void	init_fractol(t_control *ctrl, t_fractal fractal)
{
	t_fractol	res;

	res.type = fractal;
	res.max_iter = 60;
	res.anchor.re = 0.;
	res.anchor.im = 0.;
	res.zoom = 1.;
	res.radius = 2.;
	res.radius_sqrd = 4.;
//	res.iter_func = poly;
	ctrl->fractol = res;
}
/*
int		render_fractal(t_control *ctrl)
{
	
	return (0);
}*/

int			render(void *param)
{
	t_control	*ctrl;
	t_complex	tmp;
	int			i;
	int			j;

printf("REN_H = %d, REN_W = %d\n", REN_H, REN_W);
	ctrl = (t_control *)param;
	i = -1;
	while (++i < REN_H)
	{
		j = -1;
		while (++j < REN_W)
		{
			tmp.re = 1. * (i - REN_H / 2) / REN_H * ctrl->fractol.zoom;
			tmp.im = 1. * (j - REN_W / 2) / REN_W * ctrl->fractol.zoom;
			mlximg_setpixel(ctrl, get_julia_point_color(ctrl->fractol, tmp), j, i);
//printf("i = %3d; j = %3d, tmp.re = %6.2f, tmp.im = %6.2f, color = %#8x\n", i, j, tmp.re, tmp.im, get_julia_point_color(ctrl->fractol, tmp));
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	sleep(5.);
	return (0);
}
