#include "fractol.h"
/*
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
*/

int		get_julia_point_color(t_fractol frac, t_complex pt)
{
	t_u32		i;

	i = 0;
	while (i < frac.max_iter)
	{
		pt = eval_cpoly(frac.iter_func, pt);
		if (c_quadnorm(pt) > frac.radius_sqrd)
			return (i << 26 | i << 18 | i << 10);
		++i;
	}
	return (BLACK);
}

int		get_mandel_point_color(t_fractol frac, t_complex pt)
{
	t_complex	start;
	t_u32		i;

	start.re = 0.;
	start.im = 0.;
	frac.iter_func.coefs[0] = pt;
	i = 0;
	while (i < frac.max_iter)
	{
		start = eval_cpoly(frac.iter_func, start);
		if (c_quadnorm(start) > frac.radius_sqrd)
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
	t_cpoly		iter_func;
*/
void	init_fractol(t_control *ctrl, t_fractal fractal)
{
	t_fractol	res;
	t_cpoly		cpoly;

	res.type = fractal;
	res.max_iter = 20; //60. ?
	res.anchor.re = 0.;
	res.anchor.im = 0.;
	res.zoom = 5.;
	res.radius = 2.;
	res.radius_sqrd = 4.;
	cpoly.deg = 2;
	ft_bzero(cpoly.coefs, 256 * sizeof(t_complex));
	cpoly.coefs[2].re = 1.;
	cpoly.coefs[0].re = 0.5;
	cpoly.coefs[0].im = 0.5;
	res.iter_func = cpoly;
	ctrl->fractol = res;
	ctrl->frac_func = fractal == julia ? &get_julia_point_color : &get_mandel_point_color;
}

int			render(void *param)
{
	t_control	*ctrl;
	t_complex	tmp;
	int			i;
	int			j;

//printf("REN_H = %d, REN_W = %d\n", REN_H, REN_W);
	ctrl = (t_control *)param;
	i = -1;
	while (++i < REN_H)
	{
		j = -1;
		while (++j < REN_W)
		{
//printf("deb1\n");
			tmp = ctrl->fractol.anchor;
//printf("deb2 %f %f\n", tmp.re, tmp.im);
			tmp.re += ctrl->fractol.zoom * (j - REN_W / 2) / REN_W;
			tmp.im += ctrl->fractol.zoom * (i - REN_H / 2) / REN_H;
//printf("deb3 %f %f %p %p\n", tmp.re, tmp.im, ctrl->frac_func, &get_mandel_point_color);
//printf("%#x\n", ctrl->frac_func(ctrl->fractol, tmp));
			mlximg_setpixel(ctrl, ctrl->frac_func(ctrl->fractol, tmp), j, i);
//printf("i = %3d; j = %3d, tmp.re = %6.2f, tmp.im = %6.2f, color = %#8x\n", i, j, tmp.re, tmp.im, get_julia_point_color(ctrl->fractol, tmp));
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}
