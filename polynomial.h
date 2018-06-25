#ifndef POLYNOMIAL_H
# define POLYNOMIAL_H

# include "libft_math.h"

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


t_poly		str_to_poly(char const *str)
{
	
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

#endif
