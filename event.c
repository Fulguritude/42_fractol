#include "fractol.h"

int			handle_key(int key, void *param)
{
	t_control			*ctrl;
	static double		zoom_trans_ratio = 1. / 25.;

	ctrl = (t_control *)param;
	printf("key: %d\n", key);
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
	else
		return (1);
	render(ctrl);
	return (0);
}

/*
** Scroll zoom for all fractals, 
*/
void		init_events(t_control *ctrl)
{
//	int		event;
//	int		mask;

	mlx_key_hook(ctrl->win_ptr, &handle_key, ctrl);
//	mask = ;
//	mlx_mouse_hook(ctrl.win_ptr, &handle_mouse, ctrl);
//	mlx_expose_hook(ctrl.win_ptr, &handle_redraw, ctrl);
}
