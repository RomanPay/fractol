/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:45:42 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/06/13 14:50:45 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		keys(int key, t_fractol *f)
{
	set_keys_one(f, key);
	set_keys_two(f, key);
	f->img.ptr = mlx_new_image(f->mlx_ptr, WIDTH, HEIGHT);
	f->img.str = mlx_get_data_addr(f->img.ptr, &(f->img.bpp), &(f->img.s_l),
			&(f->img.endian));
	if (f->flag != f->type)
	{
		f->flag = f->type;
		set_fractal_step_two(f);
	}
	threads(f);
	f_set(*f);
	mlx_clear_window(f->mlx_ptr, f->win_ptr);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr, f->img.ptr);
	return (0);
}

int		mouse_press(int button, int x, int y, t_fractol *f)
{
	f->img.ptr = mlx_new_image(f->mlx_ptr, WIDTH, HEIGHT);
	f->img.str = mlx_get_data_addr(f->img.ptr, &(f->img.bpp), &(f->img.s_l),
			&(f->img.endian));
	if (button == 2 && f->check_button != 1)
		f->check_button = 1;
	else if (button == 2 && f->check_button == 1)
		f->check_button = 0;
	if (button == 4)
		but_4(f, x, y);
	else if (button == 5)
		but_5(f, x, y);
	threads(f);
	f_set(*f);
	mlx_clear_window(f->mlx_ptr, f->win_ptr);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr, f->img.ptr);
	return (0);
}

int		mouse_release(int button, int x, int y, t_fractol *f)
{
	f->img.ptr = mlx_new_image(f->mlx_ptr, WIDTH, HEIGHT);
	f->img.str = mlx_get_data_addr(f->img.ptr, &(f->img.bpp), &(f->img.s_l),
			&(f->img.endian));
	if (x > WIDTH - f->s && x < WIDTH && y > 0 && y < f->s && button == 1)
		f->type = 1;
	if (x > WIDTH - f->s && x < WIDTH && y > f->s && y < f->s * 2)
		f->type = 2;
	if (x > WIDTH - f->s && x < WIDTH && y > f->s * 2 && y < f->s * 3)
		f->type = 3;
	if (x > WIDTH - f->s && x < WIDTH && y > f->s * 3 && y < f->s * 4)
		f->type = 4;
	if (x > WIDTH - f->s && x < WIDTH && y > f->s * 4 && y < f->s * 5)
		f->type = 5;
	if (f->flag != f->type)
	{
		f->flag = f->type;
		set_fractal_step_two(f);
	}
	threads(f);
	f_set(*f);
	mlx_clear_window(f->mlx_ptr, f->win_ptr);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr, f->img.ptr);
	return (0);
}

int		mouse_move(int x, int y, t_fractol *f)
{
	f->img.ptr = mlx_new_image(f->mlx_ptr, WIDTH, HEIGHT);
	f->img.str = mlx_get_data_addr(f->img.ptr, &(f->img.bpp), &(f->img.s_l),
			&(f->img.endian));
	if (f->check_button != 1)
	{
		f->img.c_re = 2.0 / (f->w / x) - 1;
		f->img.c_im = 1.0 / (f->h / y) - 0.5;
	}
	if (f->flag != f->type)
	{
		f->flag = f->type;
		set_fractal_step_two(f);
	}
	threads(f);
	f_set(*f);
	mlx_clear_window(f->mlx_ptr, f->win_ptr);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.ptr, 0, 0);
	mlx_destroy_image(f->mlx_ptr, f->img.ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fractol f;

	set_fractal_step_one(&f);
	check_arg(argc, argv, &f);
	f.mlx_ptr = mlx_init();
	f.win_ptr = mlx_new_window(f.mlx_ptr, WIDTH, HEIGHT, "test");
	mlx_hook(f.win_ptr, 4, 5, mouse_press, &f);
	mlx_hook(f.win_ptr, 5, 5, mouse_release, &f);
	mlx_hook(f.win_ptr, 2, 5, keys, &f);
	mlx_hook(f.win_ptr, 6, 5, mouse_move, &f);
	mlx_hook(f.win_ptr, 17, 1L >> 17, exit_out, &f);
	mlx_loop(f.mlx_ptr);
	return (0);
}
