#include "fractol.h"

int		handle_key(int key, void *param)
{
	t_control	*ctrl;

	ctrl = (t_control *)param;
/*
	if (key == XK_KP_Space || key == XK_KP_LCtrl)
		key == XK_KP_Space ? toggle_proj(ctrl) : toggle_debug(ctrl);
	else if (key == XK_KP_Left)
		ctrl->cam.polar_pos[1] -= 0.2;
	else if (key == XK_KP_Right)
		ctrl->cam.polar_pos[1] += 0.2;
	else if (key == XK_KP_Down && ctrl->cam.polar_pos[2] - 0.1 > 0)
		ctrl->cam.polar_pos[2] -= 0.1;
	else if (key == XK_KP_Up && ctrl->cam.polar_pos[2] + 0.1 < PI)
		ctrl->cam.polar_pos[2] += 0.1;
	else if (key == XK_KP_PageDown)
		ctrl->cam.polar_pos[0] *= 1.1;
	else if (key == XK_KP_PageUp)
		ctrl->fractol[0] *= 0.9;
	else if (key == XK_KP_Esc)
		exit_error("Software closing.\n", 0);
	vec3_polar_to_cartesian(ctrl->cam.world_pos, ctrl->cam.polar_pos);
	vec3_add(ctrl->cam.world_pos, ctrl->cam.world_pos, ctrl->cam.anchor);
	ctrl->cam = init_cam(ctrl->cam.polar_pos);
*/
	handle_redraw(param);
	return (0);
}

int		handle_redraw(void *param)
{
	t_control	*ctrl;
	t_complex	tmp;
	int			i;
	int			j;

	ctrl = (t_control *)param;
	i = -1;
	while (++i < REN_H)
	{
		j = -1;
		while (++j < REN_W)
		{
			tmp.re = (i - REN_H / 2) / REN_H * ctrl->fractol.zoom;
			tmp.im = (j - REN_W / 2) / REN_W * ctrl->fractol.zoom;
			mlximg_setpixel(ctrl, get_julia_point_color(ctrl->fractol, tmp), i, j);
		}
	}
	mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr, 0, 0);
	return (0);
}

void		init_events(t_control *ctrl)
{
	int		event;
	int		mask;

	mlx_key_hook(mlx->win_ptr, handle_key, &ctrl);
//	mask = ;
}
