/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 02:25:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/15 02:25:59 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

# include "libft/hdr/libft.math"

typedef t_f64	t_float;

typedef struct	s_complex
{
	t_float		re;
	t_float		im;
}				t_complex;

typedef struct	s_complexp;
{
	t_float		rad;
	t_float		arg;
}				t_complexp;

t_complex		c_add(t_complex const z1, t_complex const z2);
t_complex		c_scl(t_float const s, t_complex const z);
t_complex		c_mul(t_complex const z1, t_complex const z2);
t_complex		c_inv(t_complex const z);

t_complexp		cexp_mul(t_complexp const radarg, t_complexp const radarg);
t_complexp		cexp_pow(t_complexp const radarg, t_float const expon);
//t_complexp		cexp_cpow(t_complexp const radarg, t_complex const expon);

t_complexp		c_cart_to_exp(t_complex const z);
t_complex		c_exp_to_cart(t_complexp const radarg);




//t_complex		cpol_mul(t_complex z1, t_complex z2);

#endif
