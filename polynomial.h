/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynomial.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:55:53 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:56:03 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

# include "libft/hdr/libft_math.h"

typedef struct	s_poly
{
	t_u8		deg;
	t_float		coefs[255];
}				t_poly;

typedef struct	s_polyfrac
{
	t_poly		num;
	t_poly		den;
}				t_polyfrac;

t_poly		str_to_poly(char const *str);
t_float		eval_poly(t_poly const poly, t_float const x);
t_float		eval_polyfrac(t_polyfrac const pf, t_float const x);
t_polyfrac	set_polyfrac(t_poly const num, t_poly const den);

#endif
