/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpolynom_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:50:21 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:50:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "polynomial.h"


# include "fractol.h"


t_cpoly		str_to_cpoly(char const *str)
{
	t_cpoly		result;
	char		**strls;
	int			i;
	t_complex	tmp;

	strls = ft_split(str, "\t ");
	i = 0;
	while (strls[i])
	{
		tmp.re = ft_atolf(strls[i]);
		tmp.im = ft_atolf(strls[i + 1]);
		result.coefs[i / 2] = tmp;
		i += 2;
	}
	result.deg = i;
	ft_strlsdel(&strls);
	return (result);
}

t_complex		eval_cpoly(t_cpoly const cpoly, t_complex const z)
{
	t_complex	result;
	int			i;

	result.re = 0.;
	result.im = 0.;
	i = cpoly.deg;
	while (i >= 0)
	{
		result = c_add(c_mul(result, z), cpoly.coefs[i]);
		--i;
	}
	return (result);
}

t_complex		eval_cpoly_fast(t_cpoly *a_cpoly, t_complex const z)
{
	t_complex	result;
	t_complex	*coefs;
	int			i;

	result.re = 0.;
	result.im = 0.;
	coefs = a_cpoly->coefs;
	i = a_cpoly->deg;
	while (i >= 0)
	{
		result = c_add(c_mul(result, z), coefs[i]);
		--i;
	}	
	return (result);
}

t_complex		eval_cpolyfrac(t_cpolyfrac const pf, t_complex const z)
{
	t_complex		num;
	t_complex		den;
	t_complex		tmp;

	num = eval_cpoly(pf.num, z);
	den = eval_cpoly(pf.den, z);
	tmp = c_inv(den);
	return (c_mul(num, tmp));
}

t_cpolyfrac	set_cpolyfrac(t_cpoly const num, t_cpoly const den)
{
	t_cpolyfrac	res;

	res.num = num;
	res.den = den;
	return (res);
}
