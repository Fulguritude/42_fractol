#include "fractol.h"

int			handle_key(int key, void *param)
{
//	t_control	*ctrl;

//	ctrl = (t_control *)param;
	printf("key: %d\n", key);
	if (key == KEY_ESC)
		exit_error("Software closing.", 0);
	render(param);
	return (0);
}

void		init_events(t_control *ctrl)
{
//	int		event;
//	int		mask;

	mlx_key_hook(ctrl->win_ptr, handle_key, &ctrl);
//	mask = ;
}
