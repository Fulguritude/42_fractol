/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 20:48:59 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/14 20:49:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** TODO : add a previous quadnorm argument to check for descendingness ?
*/

t_u8			julia_dwell(t_fractol *frac, t_complex c_pt)
{
	t_cpoly			*a_cpoly;
	t_float			lim;
	uint_fast8_t	i;

	a_cpoly = &(frac->iter_cpoly);
	lim = frac->radius_sqrd;
	i = 0;
	while (i < MAX_DWELL)
	{
		c_pt = eval_cpoly_fast(a_cpoly, c_pt);
		if (c_quadnorm(c_pt) > lim)
			return (i);
		++i;
	}
	return (i);
}

t_u8			mandel_dwell(t_fractol *frac, t_complex c_pt)
{
	t_float			lim;
	t_complex		start;
	t_cpoly			*a_cpoly;
	uint_fast8_t	i;

	lim = frac->radius_sqrd;
	a_cpoly = &(frac->iter_cpoly);
	start.re = 0.;
	start.im = 0.;
	a_cpoly->coefs[0] = c_pt;
	i = 0;
	while (i < MAX_DWELL)
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
	t_complex		prm;

	prm = c_scl(-1., frac->param);
	a_cpf = &(frac->iter_cpolyfrac);
	lim = frac->radius_sqrd;
	i = 0;
	while (i < MAX_DWELL)
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

	lim = frac->radius_sqrd;
	a_cpoly = &(frac->iter_cpoly);
	start.re = 0.;
	start.im = 0.;
	a_cpoly->coefs[0] = c_pt;
	i = 0;
	while (i < MAX_DWELL)
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
