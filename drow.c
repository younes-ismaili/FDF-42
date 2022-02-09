/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:27:49 by yismaili          #+#    #+#             */
/*   Updated: 2022/02/05 14:47:47 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_isometric(float *x, float *y, int z, fdf *ptr)
{
	float	p;

	p = *x;
	*x = (p - *y) * cos(ptr->cos_x);
	*y = (p + *y) * sin(ptr->sin_y) - z;
}

void	ft_controlerkey(fdf *ptr)
{
	ptr->z = ptr->matrix[(int)ptr->y][(int)ptr->x];
	ptr->z1 = ptr->matrix[(int)ptr->y1][(int)ptr->x1];
	ptr->x *= ptr->zom;
	ptr->x1 *= ptr->zom;
	ptr->y *= ptr->zom;
	ptr->y1 *= ptr->zom;
	ft_isometric(&ptr->x, &ptr->y, ptr->z, ptr);
	ft_isometric(&ptr->x1, &ptr->y1, ptr->z1, ptr);
	ptr->x += ptr->shift_x;
	ptr->y += ptr->shift_y;
	ptr->x1 += ptr->shift_x;
	ptr->y1 += ptr->shift_y;
}

void	ft_bresenham(fdf *ptr)
{
	float	x_step;
	float	y_step;
	float	max;

	ft_controlerkey(ptr);
	x_step = ptr->x1 - ptr->x;
	y_step = ptr->y1 - ptr->y;
	max = ft_max(abs((int)x_step), abs((int)y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(ptr->x - ptr->x1) || (int)(ptr->y - ptr->y1))
	{
		mlx_pixel_put(ptr->mlx_ptr, ptr->win_ptr, ptr->x, ptr->y, ptr->color);
		ptr->x = ptr->x + x_step;
		ptr->y = ptr->y + y_step;
	}
}

void	ft_coordinates(int x, int y, fdf *ptr, int check)
{
	if (check == 0)
	{
		ptr->x = x;
		ptr->x1 = x + 1;
		ptr->y = y;
		ptr->y1 = y;
	}
	if (check == 1)
	{
		ptr->x = x;
		ptr->x1 = x;
		ptr->y = y;
		ptr->y1 = y + 1;
	}
	ft_bresenham(ptr);
}

void	ft_drow(fdf *ptr)
{
	int	x;
	int	y;

	y = 0;
	while (y < ptr->height)
	{
		x = 0;
		while (x < ptr->width)
		{
			ptr->color = ptr->color_map[y][x];
			if (x < ptr->width - 1)
				ft_coordinates(x, y, ptr, 0);
			if (y < ptr->height - 1)
				ft_coordinates(x, y, ptr, 1);
			x++;
		}
		y++;
	}
}
