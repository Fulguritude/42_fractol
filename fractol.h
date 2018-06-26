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
# include "polynomial.h"
# include <stdio.h>
# include <mlx.h>
# include "mlx_events.h"

# define WIN_W	640
# define WIN_H	480
# define REN_W	WIN_W
# define REN_H	WIN_H

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF

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
	t_u32		max_iter;
	t_complex	anchor;
	t_float		zoom;
	t_float		radius; //convergence norm
	t_float		radius_sqrd; //convergence quadratic norm
	t_poly		iter_func;
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
	t_fractol		fractol;
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

/*
** main_fractol.c
*/
void			toggle_debug(t_control *ctrl);
void			exit_error(char *e_msg, int e_no);

/*
** image_utils.c
*/
void			mlximg_setpixel(t_control *ctrl, int color, int x, int y);
void			mlximg_clear(t_control *ctrl);
int				point_in_bounds(int x, int y);

/*
** fractals.c
*/
void			init_fractol(t_control *ctrl, t_fractal fractal);
int				get_julia_point_color(t_fractol frac, t_complex pt);
int				render(void *param);


/*
** events.c
*/
int				handle_key(int key, void *param);
void			init_events(t_control *ctrl);


t_f64			ft_atolf(char const *float_str);

#endif
