/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:50:21 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:50:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "polynomial.h"


# include "fractol.h"


t_poly		str_to_poly(char const *str)
{
	t_poly	result;
	char	**strls;
	int		i;

	strls = ft_split(str, "\t ");
	i = -1;
	while (strls[++i])
		result.coefs[i] = ft_atolf(strls[i]);
	result.deg = i;
	ft_strlsdel(&strls);
	return (result);
}

t_float		eval_poly(t_poly const poly, t_float const x)
{
	t_float	result;
	int		i;

	result = 0.;
	i = poly.deg;
	while (i >= 0)
	{
		result = result * x + poly.coefs[i];
		--i;
	}
	return (result);
}

t_float		eval_polyfrac(t_polyfrac const pf, t_float const x)
{
	t_float		num;
	t_float		den;

	num = eval_poly(pf.num, x);
	den = eval_poly(pf.den, x);
	return (num / den);
}


t_polyfrac	set_polyfrac(t_poly const num, t_poly const den)
{
	t_polyfrac	res;

	res.num = num;
	res.den = den;
	return (res);
}
