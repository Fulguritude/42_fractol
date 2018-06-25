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
		if (c_quadnorm(z) > frac->radius_sqrd)
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
	t_point		mouse; //TODO replace by t_polynomial ?
*/
void	init_fractol(t_control *ctrl)
{
	t_fractol	res;

	res.
	
	ctrl->fractol = res;
}

int		render_fractal()
{
	
}
