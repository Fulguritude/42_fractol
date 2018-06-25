/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 02:21:37 by fulguritu         #+#    #+#             */
/*   Updated: 2018/06/15 02:22:35 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/hdr/libft.h"
# include "complex.h"

typedef enum	e_fractal
{
	julia,
	mandelbrot,
	hofstadter,
	none
}				t_fractal;

typedef struct	s_fractol
{
	t_fractal	type;
	int			max_iter;
	t_complex	anchor;
	t_float		zoom;
	t_float		radius; //convergence norm
	t_float		radius_sqrd; //convergence quadratic norm
	t_point		mouse; //TODO replace by t_polynomial ?
}				t_fractol;

typedef struct	s_control
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				img_bpp;
	int				img_bpl;
	int				img_bytelen;
	int				endian;
	char			*img_data;
	t_fractol		fractal;
	int				debug;
}				t_control;

/*
** It is with this function that one creates custom hooks. funct can take
** any number/types of arguments.
**
** int	mlx_hook(t_win_list *win, int x_event, int x_mask, 
**		 int (*funct)(),void *param)
** {
**  win->hooks[x_event].hook = funct;
**  win->hooks[x_event].param = param;
**  win->hooks[x_event].mask = x_mask;
** }
*/



#endif
