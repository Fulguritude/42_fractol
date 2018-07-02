#include "fractol.h"

/*
** It is with the mlx_hook function that one creates custom hooks. funct can
** take any number/types of arguments.
**
** int	mlx_hook(t_win_list *win, int x_event, int x_mask, 
**		 int (*funct)(),void *param)
** {
**  win->hooks[x_event].hook = funct;
**  win->hooks[x_event].param = param;
**  win->hooks[x_event].mask = x_mask;
** }
*/

static int		handle_key(int key, void *param)
{
	t_control			*ctrl;
	static t_float		zoom_trans_ratio = 0.04;

	ctrl = (t_control *)param;
	printf("key: %#x\n", key);
	if (key == KEY_ESC)
		exit_error("Software closing.", 0);
	else if (key == KEY_RIGHT)
		ctrl->fractol.anchor.re -= zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_LEFT)
		ctrl->fractol.anchor.re += zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_UP)
		ctrl->fractol.anchor.im += zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_DOWN)
		ctrl->fractol.anchor.im -= zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_PAGE_UP)
		ctrl->fractol.zoom *= 1.25;
	else if (key == KEY_PAGE_DN)
		ctrl->fractol.zoom *= 0.8;
	else if (key == KEY_LCTRL)
		toggle_debug(ctrl);
	else if (key == KEY_RCTRL)
		ctrl->render_mode = !(ctrl->render_mode);
	else if (key == KEY_SPACE)
		ctrl->fractol.is_static = !(ctrl->fractol.is_static);
	else
		return (1);
	render(ctrl);
	return (0);
}


static int		handle_mouse_press(int button, int x, int y, void *param)
{
	t_control		*ctrl;
	static int		no_render = 1;

printf("mouse pressed : x %d, y %d, button %d\n", x, y, button);
	ctrl = (t_control *)param;
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		ctrl->fractol.zoom *= (button == SCROLL_UP) ? 0.9 : 1.1;
		if (no_render >= 3)
		{
			no_render = 0;
			render(ctrl);
		}
		else
			++no_render;
	}
	return (0);
}

static int		handle_mouse_release(int button, int x, int y, void *param)
{
	t_control		*ctrl;

printf("mouse released : x %d, y %d, button %d\n", x, y, button);
	ctrl = (t_control *)param;
	if (button == L_CLICK)
	{
		ctrl->fractol.anchor = get_complex_from_point(&(ctrl->fractol), x, y);
		render(ctrl);
	}
	return (OK);
}

static int		handle_mouse_move(int x, int y, void *param)
{
//	static int	prev_x = 0;
//	static int	prev_y = 0;
//	t_float		d_x;
//	t_float		d_y;
	t_control		*ctrl;
	static t_u32	no_render = 1;
	t_u32			mouse_speed;

	ctrl = (t_control *)param;
//	d_x = 1. * (x - prev_x);
//	d_y = 1. * (y - prev_y);
	if (!(ctrl->fractol.is_static))
	{
		if (ctrl->fractol.type == julia)
		{
			ctrl->fractol.iter_cpoly.coefs[0] =
				get_complex_from_point(&(ctrl->fractol), x, y);
		}
		else if (ctrl->fractol.type == mandelbrot)
		{
			ctrl->fractol.iter_cpoly.coefs[1] =
				get_complex_from_point(&(ctrl->fractol), x, y);
		}
		else if (ctrl->fractol.type == newton)
		{
			ctrl->fractol.param = get_complex_from_point(&(ctrl->fractol), x, y);
		}
		mouse_speed = (ctrl->mouse_x - x) * (ctrl->mouse_x - x) + 
					(ctrl->mouse_y - y) * (ctrl->mouse_y - y); 
//printf("mouse_speed %d\n", mouse_speed);
		if (no_render >= 4 * mouse_speed || (mouse_speed < 4 && no_render >= 5))
		{
			no_render = 0;
			render(ctrl);
		}
		else
			++no_render;
	}
	ctrl->mouse_x = x;
	ctrl->mouse_y = y;
//	prev_x = x;
//	prev_y = y;
	return (OK);
}

/*
** Scroll zoom for all fractals.
**
** MASK_POINTERMOTION returns true when the mouse moves, when no button is
**		clicked;
*/

void		init_events(t_control *ctrl)
{
	int		event;
	int		mask;

	mlx_key_hook(ctrl->win_ptr, &handle_key, ctrl);
	mask = MASK_POINTERMOTION | MASK_BUTTON1MOTION |
				MASK_BUTTON2MOTION | MASK_BUTTON3MOTION;
	event = EVENT_MOTIONNOTIFY;
	mlx_hook(ctrl->win_ptr, event, mask, handle_mouse_move, ctrl);
	mask = MASK_BUTTONPRESS;
	event = EVENT_BUTTONPRESS;
	mlx_hook(ctrl->win_ptr, event, mask, handle_mouse_press, ctrl);
	mask = MASK_BUTTONRELEASE;
	event = EVENT_BUTTONRELEASE;
	mlx_hook(ctrl->win_ptr, event, mask, handle_mouse_release, ctrl);
}
