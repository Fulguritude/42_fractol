/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 03:42:54 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/25 03:43:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/hdr/libft_math.h"

static t_f64	decim_str_to_lf(char const *str)
{
	t_u32		max_pow_ten;
	t_f64		prev_result;
	t_f64		result;
	int			i;

	prev_result = 0.;
	result = 1.;
	i = -1;
	max_pow_ten = ft_strfind(str, '.') - 1;
	while (str[++i] && result != prev_result)
	{
		if (str[i] == '.')
			continue ;
		prev_result = result;
		result += ft_lfpowi(10., --max_pow_ten) * (str[i] - '0');
	}
	return (result);
}

/*
** (exp % 2) condition solves ft_lfpowi return cases that shouldn't be -inf
** but are because of exp -= frac_digits
*/

static t_f64	expon_str_to_lf(char const *s_mant, char const *s_exp)
{
	t_f64	result;
	int		exp;
//	t_f64	mant;
	t_u8	frac_digits;

	result = (t_f64)ft_atoi(s_mant);
	exp = ft_atoi(s_exp);
	if ((frac_digits = ft_strlen(s_mant + ft_strfind(s_mant, '.'))) > 0)
	{
		result *= ft_lfpowi(10., frac_digits);
		result += ft_atoi(s_mant + ft_strfind(s_mant, '.'));
		exp -= frac_digits;
	}
	if (exp % 2)
		result *= ft_lfpowi(10., (exp + 1) / 2) * ft_lfpowi(10., (exp - 1) / 2);
	else
		result *= ft_lfpowi(10., exp / 2) * ft_lfpowi(10., exp / 2);
	return (result);
}


static t_f64	hexfp_str_to_lf(char const *s_mant, char const *s_exp, int sign)
{
	t_f64		result;
	int			exp;
	t_u64		mant;
	char		*tmp;

	result = sign ? -1. : 1.;
	tmp = ft_strremove(s_mant, "."); //TODO verif
	mant = ft_atoui_base(tmp, HXUPP);
	result *= mant;
	exp = ft_atoi(s_exp);
	exp += ft_u64bits_itoj(*(t_u64*)(&result), 1, 13) >> 51;
	*(t_u64*)(&result) &= 0x8007FFFFFFFFFFFF;
	*(t_u64*)(&result) |= (t_u64)exp << 51;
	return (result);
}

t_f64		ft_atolf(char const *float_str)
{
	char	*str;
	t_f64	result;
	char	**strls;
	int		mode;
	int		is_hexfp;

	str = ft_strdup(float_str);
	ft_str_toupper(str);
	if (!str || !*str || !ft_str_containsonly(str, "0123456789.+-EPX")
		|| ft_str_countchar(str, 'e') + ft_str_countchar(str, 'p') > 1)
		return (0. / 0.);
	is_hexfp = ft_strfind(str, 'x') > 0;
	strls = ft_split(str, is_hexfp ? "P" : "E");
	if (!(mode = ft_ptrarrlen(strls) + is_hexfp))
		return (0. / 0.);
	else if (mode == 1)
		result = decim_str_to_lf(strls[0]);
	else if (mode == 2)
		result = expon_str_to_lf(strls[0], strls[1]);
	else
		result = hexfp_str_to_lf(strls[0] + ft_strfind(strls[0], 'x'),
					strls[1], strls[0][0] == '-');
	ft_strlsdel(&strls);
	return (result);
}
