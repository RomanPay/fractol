/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color&draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:53:28 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/07 12:04:36 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	draw_pixel(int x, int y, t_color c, t_fractol *f)
{
	int		index;

	index = x * 4 + y * f->img.s_l;
	f->img.str[index] = (char)c.b;
	f->img.str[index + 1] = (char)c.g;
	f->img.str[index + 2] = (char)c.r;
}

void		set_color(double i, double x, double y, t_fractol f)
{
	t_color	color;
	double	t;

	t = i / (double)f.max_iter + f.img.color1;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (i < f.max_iter)
	{
		color.r = (int)(9 * (1 - t) * t * t * t * 255);
		color.g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		color.b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	draw_pixel(x, y, color, &f);
}
