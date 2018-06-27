#include "fractol.h"
/*
int		get_julia_dwell(t_fractol frac, t_complex pt)
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

/*
** julia_dwell
*/

t_u8		julia_dwell(t_fractol *frac, t_complex pt)
{
	t_float		lim;
	t_u8		i;

	lim = frac->radius_sqrd;
	i = 0;
	while (i < frac->max_dwell)
	{
		pt = eval_cpoly(frac->iter_func, pt);
		if (c_quadnorm(pt) > lim)
			return (i);
		++i;
	}
	return (0);
}

/*
** mandel_dwell
*/
t_u8		mandel_dwell(t_fractol *frac, t_complex pt)
{
	t_float		lim;
	t_complex	start;
	t_u8		i;

	lim = frac->radius_sqrd;
	start.re = 0.;
	start.im = 0.;
	frac->iter_func.coefs[0] = pt;
	i = 0;
	while (i < frac->max_dwell)
	{
		start = eval_cpoly(frac->iter_func, start);
		if (c_quadnorm(start) > lim)
			return (i);
		++i;
	}
	return (0);
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
void		init_fractol(t_control *ctrl, t_fractal fractal)
{
	t_fractol	res;
	t_cpoly		cpoly;

	res.type = fractal;
	res.max_dwell = 20; //60. ? //should not be strictly above 255: one needs to keep max_iter under the possibility of returning -1 (white)
	res.zoom = 5.;
	res.radius = 2.;
	res.radius_sqrd = 4.;
	res.anchor.re = 0.;
	res.anchor.im = 0.;
	cpoly.deg = 2;
	ft_bzero(cpoly.coefs, 256 * sizeof(t_complex));
	cpoly.coefs[2].re = 1.;
	cpoly.coefs[0].re = 0.5;
	cpoly.coefs[0].im = 0.5;
	res.iter_func = cpoly;
	ctrl->fractol = res;
	ctrl->frac_func = fractal == julia ? &julia_dwell : &mandel_dwell;
}

int			render(void *param)
{
	t_control	*ctrl;

	ctrl = (t_control *)param;
	if (ctrl->render_mode == 0)
		return (render_seq(ctrl));
	else
		return (render_m_s(ctrl));
}

int			render_seq(t_control *ctrl)
{
	t_complex	tmp;
	t_u32		dwell;
	int			color;
	t_s32		x;
	t_s32		y;

//printf("REN_H = %d, REN_W = %d\n", REN_H, REN_W);
	y = -1;
	while (++y < REN_H)
	{
		x = -1;
		while (++x < REN_W)
		{
//printf("deb1\n");
			tmp = get_complex_from_point(&(ctrl->fractol), x, y);
//printf("deb3 %f %f %p %p\n", tmp.re, tmp.im, ctrl->frac_func, &mandel_dwell);
//printf("%#x\n", ctrl->frac_func(ctrl->fractol, tmp));
			dwell = ctrl->frac_func(&(ctrl->fractol), tmp);
			color = (dwell << 26 | dwell << 18 | dwell << 10);
			mlximg_setpixel(ctrl, dwell == ctrl->fractol.max_dwell ?
										BLACK : color, x, y);
//printf("i = %3d; j = %3d, tmp.re = %6.2f, tmp.im = %6.2f, color = %#8x\n", i, j, tmp.re, tmp.im, get_julia_dwell(ctrl->fractol, tmp));
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}

/*
** returns the next point to be studied in Mariani-Silver
*/
#if 0
int			m_s_iter(, t_s32 x, t_s32 y)
{
	return (0);
}
#endif

/*
** An attempt to reproduce the Mariani-Silver algorithm
*/

int			render_m_s(t_control *ctrl)
{
//	int		

	mlximg_valset(ctrl, -1);

	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}
