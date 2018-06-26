/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 03:33:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/18 03:33:53 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** mlx_put_image_to_window(ctrl->mlx_ptr, ctrl->win_ptr, ctrl->img_ptr,
**							xoffset, yoffset);
*/

/*
** ctrl->img_data)[y * ctrl->img_bpl + x * ctrl->img_bpp] = color & 0xFF000000;
** ctrl->img_data)[y * ctrl->img_bpl + x * ctrl->img_bpp+1]= color & 0x00FF0000;
** etc, watch out for endianness
** The following trick only works because img_bpp = 32 / 8 = 4
*/

inline void		mlximg_setpixel(t_control *ctrl, int color, int x, int y)
{
	((t_u32 *)ctrl->img_data)[y * ctrl->img_bpl / 4 + x] = (t_u32)color;
}

inline void		mlximg_clear(t_control *ctrl)
{
	ft_bzero(ctrl->img_data, ctrl->img_bytelen);
}

inline int		point_in_bounds(int x, int y)
{
	return (0 <= x && x < REN_W && 0 <= y && y < REN_H);
}
/*
t_complex		get_complex_from_pixel(t_control ctrl, )
{

}*/
