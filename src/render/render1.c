/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: thivan-d <thivan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 14:08:58 by thivan-d      #+#    #+#                 */
/*   Updated: 2025/01/19 14:08:59 by thivan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	scale(t_vector v, double s)
{
	t_vector	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}

t_ray	create_ray(int x, int y, t_camera *camera)
{
	t_ray		ray;
	t_vector	r_vector;
	t_vector	dir[3];
	double		aspect_fov_scale;
	t_vector	image_point;

	r_vector.x = 0;
	r_vector.y = 1;
	r_vector.z = 0;
	dir[0] = normalize(camera->orientation);
	dir[1] = normalize(cross(r_vector, dir[0]));
	dir[2] = cross(dir[0], dir[1]);
	aspect_fov_scale = tan((camera->fov * M_PI / 180) / 2) * (double)WIDTH
		/ HEIGHT;
	image_point.x = (2 * (x + 0.5) / WIDTH - 1) * aspect_fov_scale;
	image_point.y = (1 - 2 * (y + 0.5) / HEIGHT) * aspect_fov_scale;
	image_point.z = 1;
	ray.origin = camera->pos;
	ray.direction = normalize(add(add(scale(dir[1], image_point.x),
					scale(dir[2], image_point.y)), scale(dir[0],
					image_point.z)));
	return (ray);
}

t_vector	cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}
