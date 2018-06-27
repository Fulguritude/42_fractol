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

# define WIN_W		640
# define WIN_H		480
# define REN_W		WIN_W
# define REN_H		WIN_H

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF


# define LINUX		0
# define MACOS		1

# define PLATFORM	LINUX //change here


#if PLATFORM
# define L_CLICK		0x1
# define R_CLICK		0x2
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

# define KEY_ESC		0x35
# define KEY_SPACE		0x31
# define KEY_LCTRL		0x3B

# define KEY_LEFT		0x7B
# define KEY_RIGHT		0x7C
# define KEY_DOWN		0x7D
# define KEY_UP			0x7E
# define KEY_PAGE_UP	0x74
# define KEY_PAGE_DN	0x79

# define KEY_HOME		0x73
# define KEY_END		0x77
# define KEY_HELP		0x72
# define KEY_DELETE		0x75

# define KEY_NUMPAD_0			0x52
# define KEY_NUMPAD_1			0x53
# define KEY_NUMPAD_2			0x54
# define KEY_NUMPAD_3			0x55
# define KEY_NUMPAD_4			0x56
# define KEY_NUMPAD_5			0x57
# define KEY_NUMPAD_6			0x58
# define KEY_NUMPAD_7			0x59
# define KEY_NUMPAD_8			0x5B
# define KEY_NUMPAD_9			0x5C
# define KEY_NUMPAD_PERIOD		0x41
# define KEY_NUMPAD_ENTER		0x4C
# define KEY_NUMPAD_ADD			0x45
# define KEY_NUMPAD_SUB			0x4E
# define KEY_NUMPAD_MUL			0x43
# define KEY_NUMPAD_DIV			0x4B
# define KEY_NUMPAD_CLEAR		0x47
# define KEY_NUMPAD_EQUALS		0x51


#else
/*
**# define XK_KP_Space					0x0020
**# define XK_KP_Tab						0xff89 //?
**# define XK_KP_Enter					0xff8d
**# define XK_KP_Left						0xff51
**# define XK_KP_Up						0xff52
**# define XK_KP_Right					0xff53
**# define XK_KP_Down						0xff54
**# define XK_KP_PageUp					0xff55
**# define XK_KP_PageDown					0xff56
**# define XK_KP_Esc						0xff1b
**# define XK_KP_LCtrl					0xffe3
*/
# define L_CLICK		0x1
# define M_CLICK		0x2
# define R_CLICK		0x3
# define SCROLL_UP		0x4
# define SCROLL_DOWN	0x5

# define KEY_ESC		0xFF1B
# define KEY_SPACE		0x0020
# define KEY_LCTRL		0xFFE3
# define KEY_RCTRL		0xFFE4

# define KEY_LEFT		0xFF51
# define KEY_UP			0xFF52
# define KEY_RIGHT		0xFF53
# define KEY_DOWN		0xFF54
# define KEY_PAGE_UP	0xFF55
# define KEY_PAGE_DN	0xFF56

# define KEY_HOME		0xFF50
# define KEY_END		0xFF57
# define KEY_INSERT		0xFF63
# define KEY_DELETE		0xFFFF

# define KEY_NUMPAD_0		0xFF9E
# define KEY_NUMPAD_1		0xFF9C
# define KEY_NUMPAD_2		0xFF99
# define KEY_NUMPAD_3		0xFF9B
# define KEY_NUMPAD_4		0xFF96
# define KEY_NUMPAD_5		0xFF9D
# define KEY_NUMPAD_6		0xFF98
# define KEY_NUMPAD_7		0xFF95
# define KEY_NUMPAD_8		0xFF97
# define KEY_NUMPAD_9		0xFF9A
# define KEY_NUMPAD_PERIOD	0xFF9F
# define KEY_NUMPAD_ENTER	0xFF8D
# define KEY_NUMPAD_ADD		0xFFAB
# define KEY_NUMPAD_SUB		0xFFAD
# define KEY_NUMPAD_MUL		0xFFAA
# define KEY_NUMPAD_DIV		0xFFAF

#endif



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
	t_u32		max_dwell;
	t_float		zoom;
	t_complex	anchor;
	t_float		radius; //convergence norm
	t_float		radius_sqrd; //convergence quadratic norm
	t_cpoly		iter_func;
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
	t_u8			(*frac_func)(t_fractol *f, t_complex z);
	int				render_mode;
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
int				handle_key(int key, void *param);
void			init_events(t_control *ctrl);


t_f64			ft_atolf(char const *float_str);

#endif
