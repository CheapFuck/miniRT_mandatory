/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:47:43 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:02:46 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// typedef struct	s_render_data
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;
// 	t_scene		*scene;
// 	int			current_row;
// 	bool		render_complete;
// }	t_render_data;

// Function declarations
// t_ray		create_ray(int x, int y, t_camera *camera);
// t_vector	world_to_local(t_vector point, t_vector orientation,
// 				t_vector center);

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

// Function to create a ray from the camera for a specific pixel
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

t_vector	world_to_local(t_vector point, t_vector orientation,
	t_vector center)
{
	t_vector	local_point;
	t_vector	up;
	t_vector	right;
	t_vector	forward;
	t_vector	temp_vector;

	local_point = subtract(point, center);
	up = orientation;
	if (fabs(up.y) < 0.999)
		temp_vector = (t_vector){0, 1, 0};
	else
		temp_vector = (t_vector){1, 0, 0};
	right = normalize(cross(up, temp_vector));
	if (fabs(up.y) < 0.999)
		temp_vector = (t_vector){0, 1, 0};
	else
		temp_vector = (t_vector){0, 1, 0};
	right = normalize(cross(up, temp_vector));
	forward = cross(right, up);
	return ((t_vector)
		{
			dot(local_point, right),
			dot(local_point, up),
			dot(local_point, forward)
		});
}

// Handle sphere intersections and update color
int	handle_spheres(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color)
{
	int			i;
	int			hit;
	double		t_sphere;
	t_vector	hit_point;
	t_vector	normal;

	hit = 0;
	i = 0;
	while (i < scene->num_spheres)
	{
		t_sphere = *t;
		if (intersect_sphere(ray, &scene->spheres[i], &t_sphere)
			&& t_sphere < *t)
		{
			*t = t_sphere;
			hit_point = add(ray->origin, multiply_scalar(ray->direction, *t));
			normal = normalize(subtract(hit_point, scene->spheres[i].center));
			*final_color = apply_lighting(hit_point, normal,
					scene->spheres[i].color, scene);
			hit = 1;
		}
		i++;
	}
	return (hit);
}
