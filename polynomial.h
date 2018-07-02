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
# include "complex.h"

# define MAX_DEGREE		256

typedef struct	s_poly
{
	t_u8			deg;
	t_float			coefs[MAX_DEGREE];
}				t_poly;

typedef struct	s_polyfrac
{
	t_poly			num;
	t_poly			den;
}				t_polyfrac;

typedef struct	s_cpoly
{
	t_u8			deg;
	t_complex		coefs[MAX_DEGREE];
}				t_cpoly;

typedef struct	s_cpolyfrac
{
	t_cpoly			num;
	t_cpoly			den;
}				t_cpolyfrac;


t_float			eval_poly(t_poly const poly, t_float const x);
t_float			eval_poly_fast(t_poly *a_poly, t_float const x);
t_float			eval_polyfrac(t_polyfrac const pf, t_float const x);
t_complex		eval_polyfrac_fast(t_polyfrac *ro_pf, t_float const x);
t_polyfrac		set_polyfrac(t_poly const num, t_poly const den);

t_complex		eval_cpoly(t_cpoly const cpoly, t_complex const z);
t_complex		eval_cpoly_fast(t_cpoly *a_cpoly, t_complex const z);
t_complex		eval_cpolyfrac(t_cpolyfrac const pf, t_complex const z);
t_complex		eval_cpolyfrac_fast(t_cpolyfrac *ro_cpf, t_complex const z);
t_cpolyfrac		set_cpolyfrac(t_cpoly const num, t_cpoly const den);

t_poly			str_to_poly(char const *str);
t_cpoly			str_to_cpoly(char const *str);
char			*poly_to_str(t_poly *ro_poly);
char			*cpoly_to_str(t_cpoly *ro_cpoly);

#endif
