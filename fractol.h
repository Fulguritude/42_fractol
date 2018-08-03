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
# include "libft/hdr/libft_io.h"
# include "libft/hdr/ft_printf.h"
# include "libft/hdr/libft_polynomial.h"
# include "mlx_event_lin.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <mlx.h>
# include <errno.h>

# define CPOLY_DIR		"./cpolys/"

# define WIN_W			480//640
# define WIN_H			320//640
# define REN_W			WIN_W
# define REN_H			WIN_H

# define BLACK			0x000000
# define RED			0xFF0000
# define GREEN			0x00FF00
# define BLUE			0x0000FF
# define WHITE			0xFFFFFF

/*
** MAX_DWELL should not be strictly above 255: one needs to keep max_iter
**		under the possibility of returning -1 (white)
** B_OFFSET = 8 - lg2(MAX_DWELL);
** G_OFFSET = B_OFFSET + 8;
** R_OFFSET = B_OFFSET + 16;
*/
# define MAX_DWELL			32
# define R_OFFSET			19
# define G_OFFSET			11
# define B_OFFSET			3

/*
**	# define NEWTONROOT_LIM		0.00001 //0.000001
** 	newtonroot,
*/
typedef enum	e_fractal
{
	julia,
	mandelbrot,
	newton,
	burningship,
	none
}				t_fractal;

typedef struct	s_point
{
	t_u16		x;
	t_u16		y;
}				t_point;

/*
** Figure struct for mariani silver: just a list of coordinates on a grid
** which draws a figure.
**
** TODO: implement another tesselation than square/quadtree
*/
typedef struct	s_figure
{
	int			pt_lst_len;
	t_point		*pt_lst;
}				t_figure;

/*
** type:			type of dwell function
** dwell_func:		escape-time fractal generating function
** zoom:			zoom on fractal (adjusts window rendering around anchor)
** anchor:			point of the complex plane around which the window is
**						centered
** radius:			radius of circle of convergence
** radius_sqrd:		quadratic radius of circle of convergence
** is_static:		if false, mouse hover alters iter_cpoly
** palette:			value that keeps track of which palette to use
** param:			param for newton dwell
** cur_coef:		index of current coef being edited by mouse movement
** iter_cpoly:		polynomial that is called by dwell_func
** iter_cpolyfrac:	polynomial fraction to be used by dwell that uses a
**						cpolyfrac
**
** TODO 	t_cpoly		negroots_cpolymul;
*/
typedef struct	s_fractol
{
	t_fractal	type;
	t_u8		(*dwell_func)(struct s_fractol *f, t_complex z);
	t_float		zoom;
	t_complex	anchor;
	t_float		radius;
	t_float		radius_sqrd;
	int			is_static;
	int			palette;
	t_complex	param;
	t_u8		cur_coef;
	t_cpoly		iter_cpoly;
	t_cpolyfrac	iter_cpolyfrac;
}				t_fractol;

/*
** mlx_ptr:			pointer to the mlx graphics server struct
** win_ptr:			pointer to the mlx window struct
** img_ptr:			pointer to the mlx image struct
** img_bpp:			number of bytes per pixel
** img_bpl:			number of bytes per line of pixels
** img_bytelen:		number of bytes in image (4 * REN_H * REN_W)
** endian:			endianness of platform
** img_data:		pointer to the image buffer
** fractol:			pointer to our fractol struct
** render_mode:		0 is pixel-by-pixel, 1 is mariani-silver, 2 is blackscreen
** debug:			true if str display of debug info on window
** mouse:			last mouse pos
*/

typedef struct	s_control
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				img_bpp;
	int				img_bpl;
	int				img_bytelen;
	int				img_pixel_nb;
	int				endian;
	char			*img_data;
	t_fractol		fractol;
	int				render_mode;
	int				debug;
	int				show_m_s;
	t_point			mouse;
}				t_control;

/*
** main_fractol.c
**
** static void			init_mlx(t_control *ctrl);
** static void			init_fractol(t_control *ctrl, t_fractal fractal);
** static void			init_events(t_control *ctrl);
** int					main(int argc, char **argv);
*/
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
**
** TODO t_u8			newtonroot_dwell(t_fractol *frac, t_complex pt);
*/
t_u8			julia_dwell(t_fractol *frac, t_complex pt);
t_u8			mandel_dwell(t_fractol *frac, t_complex pt);
t_u8			newton_dwell(t_fractol *frac, t_complex pt);
t_u8			burningship_dwell(t_fractol *frac, t_complex c_pt);

/*
** event_mouse.c
*/
int				handle_mouse_press(int button, int x, int y, void *param);
int				handle_mouse_release(int button, int x, int y, void *param);
int				handle_mouse_move(int x, int y, void *param);

/*
** event_key.c
**
** static int				handle_key_palette(int key, t_control *ctrl);
** static int				handle_key_window(int key, t_control *ctrl);
*/
int				handle_key(int key, void *param);

/*
** dwell_utils.c
*/
t_u8			get_dwell_from_point(t_control *ctrl, t_point pt);
t_u32			get_color_from_dwell(t_control *ctrl, t_u8 dwell);
void			dwell_arr_to_img(t_control *ctrl, t_u8 dwell_arr[REN_H][REN_W]);

/*
** render.c
**
** static int		render_seq(t_control *ctrl);
** static void		dwell_arr_to_img(t_control *ctrl, t_u8 *dwell_arr);
** static int		render_m_s(t_control *ctrl);
*/
int				render(void *param);

/*
** m_s_rect.c		//rectangle tesselation for mariani-silver
**
** static int 			trace_dwell_rect(t_control *ctrl, t_u8 *dwell_arr,
**									t_point anchor, t_point rect_w_h);
** static void			fill_dwell_rect(t_u8 *dwell_arr, t_u8, dwell,
**									t_point anchor, t_point rect_w_h);
** static void			rect_fill_or_divide(t_control *ctrl, t_u8 *dwell_arr,
**										t_point anchor, t_point sub_w_h);
*/
void			rect_subdivider(t_control *ctrl, t_u8 dwell_arr[REN_H][REN_W],
									t_point anchor, t_point rect_w_h);

/*
** bresenham.c
**
** static int		draw_vert(t_point *res_lst, t_point start, int endy);
** static int		draw_horz(t_point *res_lst, t_point start, int endx);
** static int		draw_vertoct(t_point *res_lst, t_point start, 
**							 t_point end, t_point d);
** static int		draw_horzoct(t_point *res_lst, t_point start,
**							 t_point end, t_point d);
*/
t_figure		get_line_points(t_point start, t_point end);

/*
** figures.c
*/
t_figure		get_rect_points(t_point anchor, t_point rect_w_h);

/*
** polynom_rdr.c
*/
t_cpoly			get_cpoly_from_filepath(char const *fpath);

#endif
