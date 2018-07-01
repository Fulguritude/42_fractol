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
# include "libft/hdr/ft_printf.h"
# include "complex.h"
# include "polynomial.h"
# include "mlx_event_lin.h"
# include <stdio.h>
# include <mlx.h>

# define WIN_W		640
# define WIN_H		480
# define REN_W		WIN_W
# define REN_H		WIN_H

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF

# define INIT_MAX_DWELL		32 //60. ? //should not be strictly above 255: one needs to keep max_iter under the possibility of returning -1 (white)

typedef enum	e_fractal
{
	julia,
	mandelbrot,
	hofstadter,
	none
}				t_fractal;

typedef struct	s_fractol
{
	t_fractal	type; //dwell mode
	t_u32		max_dwell;
	t_float		zoom;
	t_complex	anchor;
	t_float		radius; //convergence norm
	t_float		radius_sqrd; //convergence quadratic norm
	int			is_static;
	t_cpoly		iter_cpoly;
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
	t_u8			(*dwell_func)(t_fractol *f, t_complex z);
//	int				dwell_mode;
	int				render_mode;
	int				debug;
	int				mouse_x; //necessary ? if not remove
	int				mouse_y; //idem
}				t_control;

/*
** main_fractol.c
*/
void			toggle_debug(t_control *ctrl);
void			exit_error(char *e_msg, int e_no);

/*
** image_utils.c
*/
void			mlximg_setpixel(t_control *ctrl, t_s32 color, t_s32 x, t_s32 y);
void			mlximg_clear(t_control *ctrl);
int				point_in_bounds(t_s32 x, t_s32 y);
void			mlximg_valset(t_control *ctrl, t_u32 val);
t_complex		get_complex_from_point(t_fractol *frac, t_s32 x, t_s32 y);

/*
** fractals.c
*/
void			init_fractol(t_control *ctrl, t_fractal fractal);
t_u8			julia_dwell(t_fractol *frac, t_complex pt);
t_u8			mandel_dwell(t_fractol *frac, t_complex pt);
int				render(void *param);

int			render_seq(t_control *ctrl);
int			render_m_s(t_control *ctrl);

/*
** events.c
*/
//int				handle_key(int key, void *param);
void			init_events(t_control *ctrl);


t_f64			ft_atolf(char const *float_str);

#endif
