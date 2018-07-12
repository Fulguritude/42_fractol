/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 17:17:56 by fulguritu         #+#    #+#             */
/*   Updated: 2018/07/12 17:20:15 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "libft.h"

# define MAX_PALETTE_LEN 256

typedef struct	s_argb
{
	t_u8	alpha;
	t_u8	red;
	t_u8	green;
	t_u8	blue;
}				t_argb;

typedef struct	s_ahsl
{
	t_u8	alpha;
	t_u8	hue;
	t_u8	satur;
	t_u8	light;
}				t_ahsl;

typedef union	u_color
{
	t_argb	argb;
	t_ahsl	ahsl;
	t_u32	i;
}				t_color;

typedef struct	s_ipalette
{
	int		len;
	t_color	colors[MAX_PALETTE_LEN];
}				t_ipalette;

//typedef struct s_fpalette

//hsv to rgb
//rgb to hsv
//create palette from integer list
//get color from palette created by integer list

#endif
