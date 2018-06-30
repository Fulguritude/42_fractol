#include "fractol.h"

int			handle_key(int key, void *param)
{
	t_control			*ctrl;
	static double		zoom_trans_ratio = 0.04;

	ctrl = (t_control *)param;
	printf("key: %#x\n", key);
	if (key == KEY_ESC)
		exit_error("Software closing.", 0);
	else if (key == KEY_RIGHT)
		ctrl->fractol.anchor.re += zoom_trans_ratio * ctrl->fractol.zoom;
	else if (key == KEY_LEFT)
		ctrl->fractol.anchor.re -= zoom_trans_ratio * ctrl->fractol.zoom;
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
	else
		return (1);
	render(ctrl);
	return (0);
}

/*
** Scroll zoom for all fractals.
**
** MASK_POINTERMOTION returns true when the mouse moves, when no button is
**		clicked;
*/
void		init_events(t_control *ctrl)
{
//	int		event;
//	int		mask;

	mlx_key_hook(ctrl->win_ptr, &handle_key, ctrl);
//	mask = MASK_POINTERMOTION | MASK_BUTTON1MOTION |
//				MASK_BUTTON2MOTION | MASK_BUTTON3MOTION;
/*	event = EVENT_MOTIONNOTIFY;
	mlx_hook(ctrl->win_ptr, event, mask, event_mouse_move, ctrl);
	mask = MASK_BUTTONPRESS;
	event = EVENT_BUTTONPRESS;
	mlx_hook(ctrl->win_ptr, event, mask, event_mouse_press, ctrl);
	mask = MASK_BUTTONRELEASE;
	event = EVENT_BUTTONRELEASE;
	mlx_hook(ctrl->win_ptr, event, mask, event_mouse_release, ctrl);*/
}
