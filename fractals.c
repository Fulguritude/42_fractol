#include "fractol.h"

int		get_julia_point_color(t_fractol frac, t_complex pt)
{
	int			i;

	t_complex 	c;
	c.re = 1.;
	c.im = 0.;

	i = 0;
	while (i < frac.max_iter)
	{
		pt = c_add(c_mul(pt, pt), c);
		if (c_quadnorm(pt) > frac.radius_sqrd)
			return (WHITE);
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
	res.max_iter = 25;
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
