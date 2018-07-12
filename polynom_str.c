/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynom_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 01:33:14 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/29 01:49:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "polynomial.h"


#include "fractol.h"


t_poly		str_to_poly(char const *str)
{
	t_poly	result;
	char	**strls;
	int		i;

	strls = ft_split(str, "\t ");
	i = -1;
	while (strls[++i])
		result.coefs[i] = ft_atolf(strls[i]);
	result.deg = i - 1;
	ft_strlsdel(&strls);
	return (result);
}

char		*poly_to_str(t_poly *ro_poly)
{
	char	*res;
	char	*tmp;
	t_float	*coefs;
	int		i;

	res = NULL;
	tmp = NULL;
	i = ro_poly->deg;
	coefs = ro_poly->coefs;
	while (i >= 0)
	{
		ft_asprintf(&tmp, "%.3e x^%d + ", coefs[i], i);
		ft_strappend(&res, tmp);
		free(tmp);
		--i;
	}
	res[ft_strlen(res) - 7] = '\0';
	return (res);
}

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
		if (strls[i + 1])
			tmp.im = ft_atolf(strls[i + 1]);
		else
		{
			tmp.im = 0.;
			result.coefs[i / 2] = tmp;
			break;
		}
		result.coefs[i / 2] = tmp;
		i += 2;
	}
	result.deg = (i % 2) ? i / 2 : i / 2 - 1;
	ft_strlsdel(&strls);
	return (result);
}

char		*cpoly_to_str(t_cpoly *ro_cpoly)
{
	char		*res;
	char		*tmp;
	t_complex	*coefs;
	int			i;

	tmp = NULL;
	res = NULL;
	i = ro_cpoly->deg;
	coefs = ro_cpoly->coefs;
	while (i >= 0)
	{
		ft_asprintf(&tmp, "(%.3e + i*%.3e) z^%d + ",
						coefs[i].re, coefs[i].im, i);
		ft_strappend(&res, tmp);
		free(tmp);
		--i;
	}
	res[ft_strlen(res) - 7] = '\0';
	return (res);
}

char		*cpolyfrac_to_str(t_cpolyfrac *ro_cpf)
{
	char	*str;
	char	*den;
	char	*num;

	str = NULL;
	num = cpoly_to_str(&(ro_cpf->num));
	den = cpoly_to_str(&(ro_cpf->den));
	ft_asprintf(&str, "num: %s /\nden: %s", num, den);
	free(num);
	free(den);
	return (str);
}
