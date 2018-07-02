/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:49:27 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/02 15:50:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polynomial.h"

t_cpoly		derive_cpoly(t_cpoly poly)
{
	t_cpoly		deriv;
	int			i;

	deriv.deg = poly.deg - 1;
	i = poly.deg;
	while (i > 0)
	{
		deriv.coefs[i - 1] = c_scl((t_float)i, poly.coefs[i]);
		--i;
	}
	return (deriv);
}

//derive_poly
//integrate_poly
//integrate_cpoly
