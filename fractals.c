#include "fractol.h"

inline t_u8		get_dwell_from_point(t_control *ctrl, t_point pt)
{
	return (ctrl->dwell_func(
					&(ctrl->fractol),
					get_complex_from_point(&(ctrl->fractol), pt.x, pt.y)));
}

//TODO : add a previous quadnorm argument to check for descendingness ?

/*
** julia_dwell
*/

t_u8			julia_dwell(t_fractol *frac, t_complex c_pt)
{
	t_cpoly			*a_cpoly;
	t_float			lim;
	uint_fast8_t	i;
	uint_fast8_t	max_iter;

	max_iter = frac->max_dwell;
	a_cpoly = &(frac->iter_cpoly);
	lim = frac->radius_sqrd;
	i = 0;
	while (i < max_iter)
	{
		c_pt = eval_cpoly_fast(a_cpoly, c_pt);
		if (c_quadnorm(c_pt) > lim)
			return (i);
		++i;
	}
	return (i);
}

/*
** mandel_dwell
*/
t_u8			mandel_dwell(t_fractol *frac, t_complex c_pt)
{
	t_float			lim;
	t_complex		start;
	t_cpoly			*a_cpoly;
	uint_fast8_t	i;
	uint_fast8_t	max_iter;

	lim = frac->radius_sqrd;
	max_iter = frac->max_dwell;
	a_cpoly = &(frac->iter_cpoly);
	start.re = 0.;
	start.im = 0.;
	a_cpoly->coefs[0] = c_pt;
	i = 0;
	while (i < max_iter)
	{
		start = eval_cpoly_fast(a_cpoly, start);
		if (c_quadnorm(start) > lim)
			return (i);
		++i;
	}
	return (i);
}

t_u8			newton_dwell(t_fractol *frac, t_complex c_pt)
{
	t_cpolyfrac		*a_cpf;
	t_float			lim;
	uint_fast8_t	i;
	uint_fast8_t	max_iter;
	t_complex		prm;

	prm = c_scl(-1., frac->param);
	max_iter = frac->max_dwell;
	a_cpf = &(frac->iter_cpolyfrac);
	lim = frac->radius_sqrd;
	i = 0;
	while (i < max_iter)
	{
		c_pt = c_add(c_pt, c_mul(eval_cpolyfrac_fast(a_cpf, c_pt), prm));
		if (c_quadnorm(c_pt) > lim)
			return (i);
		++i;
	}
	return (i);
}

t_u8			burningship_dwell(t_fractol *frac, t_complex c_pt)
{
	t_float			lim;
	t_complex		start;
	t_cpoly			*a_cpoly;
	uint_fast8_t	i;
	uint_fast8_t	max_iter;

	lim = frac->radius_sqrd;
	max_iter = frac->max_dwell;
	a_cpoly = &(frac->iter_cpoly);
	start.re = 0.;
	start.im = 0.;
	a_cpoly->coefs[0] = c_pt;
	i = 0;
	while (i < max_iter)
	{
		start.re = start.re < 0. ? -start.re : start.re;
		start.im = start.im < 0. ? -start.im : start.im;
		start = eval_cpoly_fast(a_cpoly, start);
		if (c_quadnorm(start) > lim)
			return (i);
		++i;
	}
	return (i);
}
